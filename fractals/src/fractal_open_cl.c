#include "fractal.h"

void *kernel_exec_errors(const char *errinfo, const void *private_info, size_t cb, void *user_data)
{
	printf("kernel exec error : %s\n", errinfo);
	return (NULL);
}

void	initialize_cl_consts(t_open_cl_data *cl)
{
	void *(ptr) = kernel_exec_errors;

	cl->err = clGetPlatformIDs(1, &cl->platform, NULL);
	check_cl_error("could not determine platform", cl->err);

	clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 1, &cl->device, &cl->device_count);
	check_cl_error("could not determine device id", cl->err);

	cl->context = clCreateContext(NULL, cl->device_count, &cl->device, ptr, NULL, &cl->err);
	check_cl_error("context", cl->err);

	cl->program[0] = NULL;
}

void	build_kernel(t_open_cl_data *cl, t_window *window, char *kernel_source)
{
	cl->global_work_size[0] = SDL_WIDTH;
	cl->global_work_size[1] = SDL_HEIGHT;

	cl->program[0] = clCreateProgramWithSource(cl->context, 1, (const char **)&kernel_source, NULL, &cl->err);
	check_cl_error("could not create program from source program", cl->err);

 	cl->err = clBuildProgram(cl->program[0], cl->device_count, &cl->device, NULL, NULL, NULL);
	check_cl_error("could not build build mandel program", cl->err);

	cl->kernel[0] = clCreateKernel(cl->program[0], "mandelbrot", &cl->err);
	check_cl_error("could not build kernel", cl->err);

	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &cl->err);
	check_cl_error("could not create command queue", cl->err);

	cl->output = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, SDL_WIDTH * SDL_HEIGHT * 4, NULL, &cl->err);
	if (cl->output == NULL) { fractal_error("could not allocate memory for output"); }
	check_cl_error("could not allocate buffer", cl->err);
}	

void	set_kernel_arguments(t_open_cl_data *cl, t_fractal_data *fractal_data)
{
		cl->err = 0;
		cl->err = clSetKernelArg(cl->kernel[0], 0, sizeof(cl_mem), &cl->output);
		cl->err |= clSetKernelArg(cl->kernel[0], 1, sizeof(cl_double), &fractal_data->zoom);
		cl->err |= clSetKernelArg(cl->kernel[0], 2, sizeof(cl_double), &fractal_data->move_x);
		cl->err |= clSetKernelArg(cl->kernel[0], 3, sizeof(cl_double), &fractal_data->move_y);
		cl->err |= clSetKernelArg(cl->kernel[0], 4, sizeof(int), &fractal_data->width);
		cl->err |= clSetKernelArg(cl->kernel[0], 5, sizeof(int), &fractal_data->height);
		cl->err |= clSetKernelArg(cl->kernel[0], 6, sizeof(int), &fractal_data->color_depth);
		cl->err |= clSetKernelArg(cl->kernel[0], 7, sizeof(int), &fractal_data->bpl);
		check_cl_error("failed to set kernel args", cl->err);
}

void	execute_kernel(t_open_cl_data *cl, t_window *window)
{
	cl->err = clEnqueueNDRangeKernel(cl->queue, cl->kernel[0], 2, NULL, cl->global_work_size, NULL, 0, NULL, NULL);
	check_cl_error("Failed to execute kernel", cl->err);	

	clFinish(cl->queue);

	clEnqueueReadBuffer(cl->queue, cl->output, CL_TRUE, 0, SDL_WIDTH * SDL_HEIGHT * 4, SDL_FRAME_BUFFER, 0, NULL, NULL);
}
