#include "fractal.h"

void					free_if(void *ptr)
{
	if (ptr)
		free(ptr);
}
