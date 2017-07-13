#ifndef __MACROS_H
# define __MACROS_H

# define DEFAULT_WIDTH			800
# define DEFAULT_HEIGHT			600	
# define DEFAULT_COLOR_DEPTH	32
# define SDL_WINDOW				window->window
# define SDL_SCREEN				window->screen
# define SDL_IMAGE				window->image
# define SDL_FRAME_BUFFER		window->frame_buffer
# define SDL_WIDTH				window->width
# define SDL_HEIGHT				window->height
# define SDL_DEPTH				window->depth
# define SDL_BPL				window->bytes_per_line
# define SDL_EVENT				window->event
# define KEY					SDL_EVENT.key.keysym.sym

enum	e_fractals
{
	MANDEL = 0,
	JULIA = 1,
	NEWTON = 2,
};

#endif
