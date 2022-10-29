/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coloring_methods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 19:21:32 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Colors.h>

uint32_t	ft_color_method_0(t_fractal *fractal, double i)
{
	double		temp;
	int			shift;
	uint32_t	color;

	temp = ((double)i / fractal->max_iter) * 5;
	if (temp > 1.0f)
		temp = 1.0f;
	else if (temp < 0.0f)
		temp = 0.0f;
	shift = temp * 255;
	color = (shift << 16) | (shift << 8) | shift;
	return (color);
}

uint32_t	ft_color_method_123(t_fractal *fractal, double i)
{
	double		temp;
	uint32_t	color;
	uint32_t	*palette;

	temp = ((double)i / fractal->max_iter);
	palette = fractal->palette;
	if (fractal->color_method == 1)
		color = temp * 0x777777;
	if (fractal->color_method == 2)
		color = ft_bernstein_interpolation(temp);
	if (fractal->color_method == 3)
		color = ft_linear_interpolation(palette[0], palette[8], temp);
	return (color);
}
