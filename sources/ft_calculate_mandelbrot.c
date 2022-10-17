/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/17 23:09:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_cal_mandelbrot(t_img *img, t_mdbt mdbt)
{
	int	i;
	int	j;

	i = mdbt.y;
	while (i < mdbt.y + mdbt.height)
	{
		j = mdbt.x;
		while (j < mdbt.x + mdbt.width)
			img_pix_put(img, j++, i, mdbt.color);
		++i;
	}
	return (0);
}
