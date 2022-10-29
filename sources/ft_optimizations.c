/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimizations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 18:53:01 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

	/* function for mandelbrot allowing us to memcpy the "big size" **
	**and saving time. We apply the same formulae as mxl_put pixel on img */
void	ft_optimization_symmetry(t_data *data, t_distance *y)
{
	t_img		*img;
	t_fractal	*fractal;
	size_t		py;

	img = &data->img;
	fractal = data->fractal;
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
}

int	ft_check_shapes(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	double	q;

	q = pow(fractal->px_coord.x - 0.25, 2) + (fractal->px_coord.y * fractal->px_coord.y);
	if (0.25 * fractal->px_coord.y * fractal->px_coord.y >= (q * (q + (fractal->px_coord.x - 0.25))) ||
		(pow(fractal->px_coord.x + 1, 2) + (fractal->px_coord.y * fractal->px_coord.y) <= (double)1/16))
	{
		if (fractal->fractal_type == 3)
			img_pix_put(img, px, py, 0x000000);
		else
			img_pix_put(img, px, py, ft_color_fractal(fractal, fractal->max_iter));
		return (1);
	}
	return (0);
}

int	ft_check_period(t_fractal *fractal, double *period, size_t *i)
{
	if (fractal->polar_coord.x == fractal->old.x && fractal->polar_coord.y == fractal->old.y)
	{
		*i = fractal->max_iter;
		return (1);
	}
	*period = *period + 1;
	if (*period > 4)
	{
		*period = 0;
		fractal->old.x = fractal->polar_coord.x;
		fractal->old.y = fractal->polar_coord.y;
	}
	return (0);
}
