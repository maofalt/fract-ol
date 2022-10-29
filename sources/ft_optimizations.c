/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimizations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 14:52:49 by motero           ###   ########.fr       */
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
