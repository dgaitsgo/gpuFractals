__kernel void mandelbrot(__global char *output,
double zoom,
double move_x,
double move_y,
int	width,
int height,
int color_depth,
int bpl)
{
	int idx = get_global_id(0);
	int	idy = get_global_id(1);
	int i;

	int max_iter, iter;
	double pr, pi, old_re, old_im, new_re, new_im; 

	new_re = 0;
	new_im = 0;
	old_re = 0;
	old_im = 0;
	max_iter = 400;

	pr = 1.5 * (idx - width / 2.0) / (0.5 * zoom * width) + move_x;
	pi = (idy - height / 2) / (0.5 * zoom * height) + move_y;
	iter = 0;
	while (iter < max_iter)
	{
		old_re = new_re;
		old_im = new_im;
		new_re = old_re * old_re - old_im * old_im + pr;
		new_im = 2 * old_re * old_im + pi;
		if ((new_re * new_re + new_im * new_im) > 4)	
			break ;
		iter++;
	}
	i = (idx * color_depth >> 3) + idy * bpl;
	output[i] 		= iter % 256;
	output[i + 1] 	= old_re * 4 / new_re; 
	output[i + 2] 	= 255 * (iter < max_iter);
	output[i + 3] 	= 1;
}
