#include "fractal.h"

int		valid_key(int key)
{
	if (key == SDLK_PLUS_MAC || key == SDLK_PLUS || key == SDLK_MINUS)
		return (ZOOM_EVENT);
	if (key == SDLK_LEFT || key == SDLK_UP || key == SDLK_RIGHT || key == SDLK_DOWN)
		return (MOVE_EVENT);
	return (INVALID);
}

void	poll_events(t_fractal *env)
{
	t_window		*window = env->window;
	t_fractal_data	*fractal_data = env->fractal_data;
	int quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&SDL_EVENT))
		{
			if (valid_key(KEY))
			{
				if (KEY == SDLK_PLUS_MAC || KEY == SDLK_PLUS)
					fractal_data->zoom *= 1.15;
				else if (KEY == SDLK_MINUS)
					fractal_data->zoom /= 1.15;
				else if (KEY == SDLK_LEFT)
					fractal_data->move_x -= 0.3 / fractal_data->zoom;
				else if (KEY == SDLK_UP)
					fractal_data->move_y -= 0.3 / fractal_data->zoom;
				else if (KEY == SDLK_RIGHT)
					fractal_data->move_x += 0.3 / fractal_data->zoom;
				else if (KEY == SDLK_DOWN)
					fractal_data->move_y += 0.3 / fractal_data->zoom;
				set_kernel_arguments(env->cl, fractal_data);
				execute_kernel(env->cl, env->window);
				put_image(env);
			}
			if (SDL_EVENT.type == SDL_QUIT || KEY == SDLK_ESCAPE)
			{
				quit = 1;
				kill_sdl(window);
			}
		}
	}
}
