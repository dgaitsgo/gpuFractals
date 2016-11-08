__kernel void newton(__global char *output,
float zoom,
float move_x,
float move_y,
int max_iter,
int width,
int height,
int color_depth,
int bpl)
{
	int idx = get_global_id(0);
	int idy = get_global_id(1);
	int i, iter;

	float old_re, new_re, old_im, new_im, temp;

	iter = 0;
	new_re = 1.5 * (idx - width / 2) / (0.5 * zoom * width) + move_x;
	new_im = (idy - height / 2) / (0.5 * zoom * height) + move_y;
	temp = 1.0;
	while (temp > 0.000001 && iter++ < max_iter)
	{
		old_re = new_re;
		old_im = new_im;
		temp = (new_re * new_re + new_im * new_im) * (new_re * new_re + new_im * new_im);
		new_re = (2 * new_re * temp + new_re * new_re - new_im * new_im) / (3.0 * temp);
		new_im = (2 * new_im * (temp - old_re)) / (3.0 * temp);
		temp = (new_re - old_re) * (new_re - old_re) + (new_im - old_im) * (new_im - old_im);
	}

	i = (idx * color_depth >> 3) + idy * bpl;
	output[i] 		= iter % 256;
	output[i + 1] 	= temp * 13; 
	output[i + 2] 	= 144 * old_im;
	output[i + 3] 	= 1;
}
