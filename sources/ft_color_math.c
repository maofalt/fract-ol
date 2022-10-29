/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 19:04:37 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Colors.h>

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
