#ifndef __WINDOW_H
# define __WINDOW_H

#include <SDL2/SDL.h>

typedef	struct			s_window
{
	SDL_Window			*window;
	SDL_Surface			*screen;
	SDL_Surface			*image;
	SDL_Event			event;
	char				*frame_buffer;
	int					fractal_type;
	int					width;
	int					height;
	int					depth;
	int					bytes_per_line;
}						t_window;

void					initialize_window_data(t_window *window);
void					initialize_window(t_window *window);
void					kill_sdl(t_window *window);
#endif
