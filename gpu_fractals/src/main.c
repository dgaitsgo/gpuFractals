#include "fractal.h"

t_fractal_data	*initialize_mandel(t_window *window)
{
	t_fractal_data *m = new_fractal_data();
	set_default_fractal_data(m, window);

	m->move_x = -0.5;
	m->move_y = 0;
	m->max_iter = 400;
	return (m);
}

t_fractal_data *initialize_newton(t_window *window)
{
	t_fractal_data *n = new_fractal_data(); 
	set_default_fractal_data(n, window);

	n->move_x = 0;
	n->move_y = 0;
	n->max_iter = 100;
	return (n);
}

t_fractal_data *initialize_julia(t_window *window)
{
	t_fractal_data *j = new_fractal_data(); 
	set_default_fractal_data(j, window);

	j->move_x = 0;
	j->move_y = 0;
	j->max_iter = 100;
	return (j);
}

void		*initialize_fractal(t_open_cl_data *cl, t_window *window, char *arg_name)
{
	void	*fractal_data;
	char	*kernel_source;
	int		fd;

	initialize_window(window);
	initialize_cl_consts(cl);

	fd = -1;
	if (ft_strcmp(arg_name, "mandelbrot") == 0)
	{
		fractal_data = initialize_mandel(window);
		fd = open("./kernels/mandelbrot.cl", O_RDONLY);
		window->fractal_type = MANDEL;
	}
	if (ft_strcmp(arg_name, "julia") == 0)
	{
		fractal_data = initialize_julia(window);
		fd = open("./kernels/julia.cl", O_RDONLY);
		window->fractal_type = JULIA;
	}
	if (ft_strcmp(arg_name, "newton") == 0)
	{
		fractal_data = initialize_newton(window);
		fd = open("./kernels/newton.cl", O_RDONLY);
		window->fractal_type = NEWTON;
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
