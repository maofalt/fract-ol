/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 02:20:05 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

/* We render fracta if update == 1, in this case if a hook or **
**event has modified underlying constants*/
int	ft_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (data->fractal->update)
	{
		ft_render_fractal(&data->img, data->fractal);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
		data->fractal->update = 0;
	}
	return (0);
}

/*Deprecated functions, for test and debug functions intended **
**to fill mlx_img with one color*/
void	ft_render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

	/*For mandelbrot (except 2) we optimize only calculation have of it**
	 with symmtry of the Real axis. For this wedetect the size imaginary **
	 **size the the most pixel and limit our calculation to only that side.
	 This willa llow us to memcpy to ther other side, saving calculation time
	**/
void	ft_calculation_limits(t_fractal *fractal, t_distance *y)
{
	if (fractal->fractal_type == 1)
	{
		if (fractal->xtrm.im_min < 0 && fractal->xtrm.im_max > 0)
		{
			if (fractal->xtrm.im_max + fractal->xtrm.im_min >= 0)
				y->max = ((fractal->xtrm.im_max * WINDOW_HEIGHT)
						/ (fractal->xtrm.im_max - fractal->xtrm.im_min)) + 1;
			else
				y->min = ((fractal->xtrm.im_max * WINDOW_HEIGHT)
						/ (fractal->xtrm.im_max - fractal->xtrm.im_min));
		}
	}
	else if (fractal->fractal_type >= 2 && fractal->fractal_type <= 4)
	{
		y->min = 0;
		y->max = WINDOW_HEIGHT;
	}
}

/*replace t_img *img, t_fractal *fractal by t_data *data */
int	ft_render_fractal(t_img *img, t_fractal *fractal)
{
	size_t			px;
	size_t			py;
	t_distance		*y;

	y = malloc(sizeof(t_distance));
	if (y == NULL)
		return (1);
	y->min = 0;
	y->max = WINDOW_HEIGHT;
	ft_recenter_fractal(fractal, y);
	/*create void	ft_calculate_pixels(t_data *data, t_distance y) creae px,py in new function and  */
	py = 0;
	py = y->min;
	while (py <= y->max)
	{
		px = 0;
		while (px < WINDOW_WIDTH)
		{
			if (fractal->fractal_type == 1 || fractal->fractal_type == 3)
				ft_calculate_mandelbrot(img, fractal, px, py);
			else if (fractal->fractal_type == 2)
				ft_calculate_julia(img, fractal, px, py);
			else if (fractal->fractal_type == 4)
				ft_calculate_burning_ship(img, fractal, px, py);
			px++;
		}
		py++;
	}
	/*stop here*/
	/* function for mandelbrot allowing us to memcpy the "big size" and saving time**
	**weapply the same formulae as mxl_put pixel on img */
/*void ft_optimization_symmetry( t_data *data, t_distance) create again size py*/
	if (fractal->fractal_type == 1)
	{
		py = 0;
		while (py <= y->min)
		{
			ft_memcpy(img->addr + ((py) * img->line_len), img->addr
				+ (img->line_len * (2 * y->min - py)), img->line_len);
			py++;
		}
		py = y->max;
		while (py <= WINDOW_HEIGHT)
		{
			ft_memcpy(img->addr + ((py) * img->line_len), img->addr
				+ (img->line_len * (2 * y->max - py)), img->line_len);
			py++;
		}
	}
	/* stop here */
	free(y);
	return (0);
}