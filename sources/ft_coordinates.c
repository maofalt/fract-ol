/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/23 01:23:59 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

t_coord	ft_initialize_coord(void)
{
	t_coord	coord;

	coord.x = 0;
	coord.y = 0;
	return (coord);
}

t_coord	ft_initialize_offset(size_t fractal_type)
{
	t_coord	offset;

	if (fractal_type == 1)
	{
		offset.x = -2;
		offset.y = 1.12;
	}
	else if (fractal_type == 2)
	{
		offset.x = -2;
		offset.y = 2;
	}
	return (offset);
}

t_xtrm	ft_initialize_extremes(size_t fractal_type)
{
	t_xtrm	xtrm;

	if (fractal_type == 1)
	{
		xtrm.re_max = 0.47;
		xtrm.re_min = -2;
		xtrm.im_max = 1.12;
		xtrm.im_min = -1.12;
	}
	else if (fractal_type == 2)
	{
		xtrm.re_max = 2;
		xtrm.re_min = -2;
		xtrm.im_max = 2;
		xtrm.im_min = -2;
	}
	return (xtrm);
}

t_zoom	ft_initialize_zoom(size_t fractal_type)
{
	t_zoom	zoom;

	if (fractal_type == 1)
	{
		zoom.kx = 2.47 / WINDOW_WIDTH;
		zoom.ky = 2.24 / WINDOW_HEIGHT;
	}
	else if (fractal_type == 2)
	{
		zoom.kx = 4 / WINDOW_WIDTH;
		zoom.ky = 4 / WINDOW_HEIGHT;
	}
	return (zoom);
}
