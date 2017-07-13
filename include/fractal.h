#ifndef __FRACTAL_H
# define __FRACTAL_H

//global
#include <SDL2/SDL.h>
#include <OpenCL/opencl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

//locals
#include "macros.h"
#include "parse.h"
#include "get_next_line.h"
#include "open_cl_fractal.h"
#include "window.h"
#include "events.h"

typedef struct			s_fractal_data
{
	float			zoom;
	float			move_x;
	float			move_y;
	int					max_iter;
	int					width;
	int					height;
	int					bpl;
	int					color_depth;
}						t_fractal_data;

typedef struct			s_fractal
{
	t_window			*window;
	t_open_cl_data		*cl;
	t_fractal_data		*fractal_data;
	int					fractal_type;
}						t_fractal;


void					set_default_fractal_data(t_fractal_data *data, t_window *window);
t_fractal_data			*new_fractal_data(void);
void					set_kernel_arguments(t_open_cl_data *cl, t_fractal_data *fractal_data);
void					free_if(void *ptr);
char					*file_to_string(const int fd);
void					check_cl_error(char *title, cl_int err);
void					fractal_error(char *title);
void					put_image(t_fractal *env);
void					poll_events(t_fractal *env);

# endif
