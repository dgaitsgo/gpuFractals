#ifndef __FRACTAL_OPEN_CL
# define __FRACTAL_OPEN_CL

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#include "window.h"

typedef	struct
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue 	queue;
	cl_uint				device_count;
	cl_int 				i;
	cl_int				err;
	cl_program			program[1];
	cl_kernel			kernel[1];
	cl_mem				output;
	size_t				local_work_size[2];
	size_t				global_work_size[2];
}						t_open_cl_data;

void 	*kernel_exec_errors(const char *errinfo, const void *private_info, size_t cb, void *user_data);
void	initialize_cl_consts(t_open_cl_data *cl);
void	build_kernel(t_open_cl_data *cl, t_window *window, char *kernel_source);
void	execute_kernel(t_open_cl_data *cl, t_window *window);

#endif
