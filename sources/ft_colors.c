/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 19:26:31 by motero           ###   ########.fr       */
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

uint32_t	ft_color_fractal(t_fractal *fractal, double i)
{
	uint32_t		color;

	color = 0;
	if (fractal->color_method == 0)
		color = ft_color_method_0(fractal, i);
	else if (fractal->color_method == 1 || fractal->color_method == 2
		|| fractal->color_method == 3)
		color = ft_color_method_123(fractal, i);
	else if (fractal->color_method == 4 || fractal->color_method == 5)
		color = ft_color_method_45(fractal, i);
	return (color);
}
