#include "fractal.h"

t_fractal_data	*initialize_mandel(t_window *window)
{
	t_fractal_data *m = malloc(sizeof(t_fractal_data));

	m->zoom = 1;
	m->move_x = -0.5;
	m->move_y = 0;
	m->color_depth = SDL_DEPTH;
	m->bpl = SDL_BPL;
	m->width = SDL_WIDTH;
	m->height = SDL_HEIGHT;
	return (m);
}

void		*initialize_fractal(t_open_cl_data *cl, t_window *window, char *arg_name)
{
	void	*fractal_data;
	char	*kernel_source;
	int		fd;
	short	fractal_type;

	initialize_window(window);
	initialize_cl_consts(cl);

	fd = -1;
	if (ft_strcmp(arg_name, "mandel") == 0)
	{
		fractal_data = initialize_mandel(window);
		fd = open("./kernels/mandel.cl", O_RDONLY);
		fractal_type = MANDEL;
	}

	if (fd <= 2)
		fractal_error("invalid kernel file");
	kernel_source = file_to_string(fd);

	build_kernel(cl, window, kernel_source);	
	set_kernel_arguments(cl, fractal_data);
	return (fractal_data);
}

int main(int argc, char **argv)
{
	t_fractal		env;
	t_open_cl_data	*cl;
	t_window		*window;

	if (argc != 2)
		fractal_error("usage : ./fractal [mandel]");

	cl		= malloc(sizeof(t_open_cl_data));
	window	= malloc(sizeof(t_window));

	env.fractal_data = initialize_fractal(cl, window, argv[1]);
	env.cl = cl;
	env.window = window;
	execute_kernel(cl, window);
	put_image(&env);
	return (0);
}
