#include "fractal.h"

void	check_cl_error(char *title, cl_int err)
{
	if (err != CL_SUCCESS)
	{
		printf("%s\n", title);
		exit(0);
	}
}

void	fractal_error(char *title)
{
	printf("%s\n", title);
	exit(0);
}
