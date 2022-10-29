/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 19:01:45 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Colors.h>

/* Encode of 4 unint8_t into a utin32_t, so mlx is able to read RGB in Hex,**
** thourgh bit shifting. */
uint32_t	encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue)
{
	return (hue << 24 | red << 16 | green << 8 | blue);
}

uint32_t	*ft_intialize_palette(void)
{
	uint32_t	*palette;

	palette = malloc(sizeof(uint32_t) * 9);
	if (!palette)
		return (NULL);
	palette[0] = C1;
	palette[1] = C2;
	palette[2] = C3;
	palette[3] = C4;
	palette[4] = C5;
	palette[5] = C6;
	palette[6] = C7;
	palette[7] = C8;
	palette[8] = C9;
	return (palette);
}

uint32_t	ft_bernstein_interpolation(double temp)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = 9 * (1 - temp) * pow(temp, 3) * 255;
	g = 15 * pow((1 - temp), 2) * pow(temp, 2) * 255;
	b = 8.5 * pow(1 - temp, 3) * temp * 255;
	return (encode_rgb(1, r, g, b));
}

uint32_t	ft_linear_interpolation(uint32_t col1, uint32_t col2, double temp)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	rgb1;
	uint8_t	rgb2;

	rgb1 = (col1 >> 16) & 0xff;
	rgb2 = (col2 >> 16) & 0xff;
	r = rgb1 +(rgb2 - rgb1) * temp;
	rgb1 = (col1 >> 8) & 0xff;
	rgb2 = (col2 >> 8) & 0xff;
	g = rgb1 +(rgb2 - rgb1) * temp;
	rgb1 = col1 & 0xff;
	rgb2 = col2 & 0xff;
	b = rgb1 +(rgb2 - rgb1) * temp;
	return (encode_rgb(1, r, g, b));
}

uint32_t	ft_color_fractal(t_fractal *fractal, double i)
{
	uint32_t		color = 0, color1 = 0, color2 = 0;
	double			temp;
	int				shift;
	const size_t	color_max = 0x777777;
	double			log_zn;
	double			nu = 0;

	color = 0;
	if (fractal->color_method == 0)
	{	
		temp = ((double)i / fractal->max_iter) * 5;
		if (temp > 1.0f)
			temp = 1.0f;
		else if (temp < 0.0f)
			temp = 0.0f;
		shift = temp * 255;
		color = (shift << 16) | (shift << 8) | shift;
	}
	else if (fractal->color_method == 1 || fractal->color_method == 2 || fractal->color_method == 3)
	{
		temp = ((double)i / fractal->max_iter);
		if (fractal->color_method == 1)
			color = temp * (double)color_max;
		if (fractal->color_method == 2)
			color = ft_bernstein_interpolation(temp);
		if (fractal->color_method == 3)
			color = ft_linear_interpolation(fractal->palette[0], fractal->palette[8], temp);
	}
	else if (fractal->color_method == 4 || fractal->color_method == 5)
	{
		nu = i;
		if (floor(i) < fractal->max_iter)
		{
			log_zn = log(fractal->sq_coord.x + fractal->sq_coord.y) / 2;
			nu = i + 1 - log(log_zn / log(2)) / log(2);
		}
		else
			return (fractal->palette[0]);
		color1 = fractal->palette[(int)(nu) % 9];
		color2 = fractal->palette[((int)(nu) + 1) % 9];
		temp = nu - floor(nu);
		if (fractal->color_method == 4)
			color = ft_bernstein_interpolation(temp);
		if (fractal->color_method == 5)
			color = ft_linear_interpolation(color1, color2, temp);
	}
	return (color);
}
