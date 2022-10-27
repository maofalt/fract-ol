/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 01:15:52 by motero           ###   ########.fr       */
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

	offset = ft_initialize_coord();
	if (fractal_type == 1 || fractal_type == 3)
	{
		offset.x = -2;
		offset.y = 1.12;
	}
	else if (fractal_type == 2)
	{
		offset.x = -2;
		offset.y = 2;
	}
	else if (fractal_type == 4)
	{
		offset.x = -2.5;
		offset.y = 1;
	}
	return (offset);
}

t_xtrm	ft_initialize_extremes(size_t fractal_type)
{
	t_xtrm	xtrm;

	if (fractal_type == 1 || fractal_type == 3)
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
	else if (fractal_type == 4)
	{
		xtrm.re_max = 1;
		xtrm.re_min = -2.5;
		xtrm.im_max = 1;
		xtrm.im_min = -1;
	}
	else
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

	if (fractal_type == 1 || fractal_type == 3)
	{
		zoom.kx = 2.47 / WINDOW_WIDTH;
		zoom.ky = 2.24 / WINDOW_HEIGHT;
	}
	else if (fractal_type == 2)
	{
		zoom.kx = 4.0 / WINDOW_WIDTH;
		zoom.ky = 4.0 / WINDOW_HEIGHT;
	}
	if (fractal_type == 4)
	{
		zoom.kx = 4.0 / WINDOW_WIDTH;
		zoom.ky = 3.0 / WINDOW_HEIGHT;
	}
	else
	{
		zoom.kx = 0;
		zoom.ky = 0;
	}
	return (zoom);
}

t_coord	ft_initialize_complexe(t_fractal fractal, char **argv, int argc)
{
	t_coord	cmplx;

	if (fractal.fractal_type == 1)
		cmplx = ft_initialize_coord();
	else if (fractal.fractal_type == 2 && argc == 2)
	{
		cmplx.x = 0.5;
		cmplx.y = -0.5;
	}
	else if (fractal.fractal_type == 2 && argc < 5)
	{
		cmplx.x = ft_atof(argv[2]);
		cmplx.y = ft_atof(argv[3]);
		printf("During %f %f\n", cmplx.x, cmplx.y);
	}
	else
		cmplx = ft_initialize_coord();
	printf("end %f %f\n", cmplx.x, cmplx.y);
	return (cmplx);
}
