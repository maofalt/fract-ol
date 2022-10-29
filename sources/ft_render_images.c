/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 23:43:19 by motero           ###   ########.fr       */
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
		ft_render_fractal(data);
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

	/* pan into each px & apply and apply sequence formula 'til escape radius*/
void	ft_calculate_pixels(t_data *data, t_distance *y)
{
	size_t			px;
	size_t			py;
	t_img			*img;
	t_fractal		*fractal;

	img = &data->img;
	fractal = data->fractal;
	py = 0;
	py = y->min;
	while (py <= y->max)
	{
		px = 0;
		while (px < WINDOW_WIDTH)
		{
			if (fractal->fractal_type == 1 || fractal->fractal_type == 3)
				ft_cal_mandel(img, fractal, px, py);
			else if (fractal->fractal_type == 2)
				ft_cal_julia(img, data->fractal, px, py);
			else if (fractal->fractal_type == 4)
				ft_cal_burn_ship(img, data->fractal, px, py);
			px++;
		}
		py++;
	}
}

/*replace t_img *img, t_fractal *fractal by t_data *data */
int	ft_render_fractal(t_data *data)
{
	t_distance		*y;

	y = malloc(sizeof(t_distance));
	if (y == NULL)
		return (1);
	y->min = 0;
	y->max = WINDOW_HEIGHT;
	ft_calculation_limits(data->fractal, y);
	ft_calculate_pixels(data, y);
	ft_optimization_symmetry(data, y);
	free(y);
	return (0);
}
