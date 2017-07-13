#include "fractal.h"


void			set_default_fractal_data(t_fractal_data *data, t_window *window)
{
	data->zoom = 1;
	data->color_depth = SDL_DEPTH;
	data->bpl = SDL_BPL;
	data->width = SDL_WIDTH;
	data->height = SDL_HEIGHT;
}

t_fractal_data *new_fractal_data()
{
	t_fractal_data *new = malloc(sizeof(t_fractal_data));
	if (!new)
		exit(0);
	return (new);
}
