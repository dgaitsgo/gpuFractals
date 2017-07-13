#include "fractal.h"

void	put_image(t_fractal *env)
{
	t_window *window = env->window;

	SDL_BlitSurface(SDL_IMAGE, NULL, SDL_SCREEN, NULL);
	SDL_UpdateWindowSurface(SDL_WINDOW);
	poll_events(env);
}

void	initialize_window_data(t_window *window)
{	
	SDL_WIDTH = DEFAULT_WIDTH;
	SDL_HEIGHT = DEFAULT_HEIGHT;
	SDL_DEPTH = DEFAULT_COLOR_DEPTH;
	SDL_BPL = SDL_WIDTH * (SDL_DEPTH / 8);
}

void	initialize_window(t_window *window)
{
	initialize_window_data(window);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WINDOW = SDL_CreateWindow("gpu_fractals", 0, 0,
	SDL_WIDTH, SDL_HEIGHT, 0);
	SDL_SCREEN = SDL_GetWindowSurface(SDL_WINDOW);
	SDL_FRAME_BUFFER = malloc(SDL_WIDTH * SDL_HEIGHT * 4);
	SDL_IMAGE = SDL_CreateRGBSurfaceFrom(SDL_FRAME_BUFFER,
	SDL_WIDTH, SDL_HEIGHT, SDL_DEPTH, SDL_BPL, 0, 0, 0, 0);
}

void	kill_sdl(t_window *window)
{
	SDL_FreeSurface(window->image);
	SDL_FreeSurface(window->screen);
	SDL_DestroyWindow(SDL_WINDOW);
	SDL_Quit();
	exit(0);
}
