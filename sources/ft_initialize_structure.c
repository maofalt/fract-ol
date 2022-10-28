/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize_structure.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 23:18:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

/*After validating, that args are OK, we parse  the fractal_type (ft) **
** 1 - "mandelbrot"  or "mandelbrot 1"--> ft = 1 **
** 2 - "mandelbrot 1"--> ft = 3 **
** 3 - "julia" or "julia %f %f"--> ft = 2 **
** 4 - "burning_ship -- > ft = 4 "*/
size_t	ft_initialize_fractal_type(int argc, char **argv)
{
	size_t	w_len;

	w_len = ft_strlen(argv[1]);
	if (!ft_strncmp(argv[1], "mandelbrot", w_len))
	{
		if (argc == 2 || (argc == 3 && argv[2][0] == '1'))
			return (1);
		if (argc == 2 || (argc == 3 && argv[2][0] == '2'))
			return (3);
	}
	else if (!ft_strncmp(argv[1], "julia", w_len))
		return (2);
	else if (!ft_strncmp(argv[1], "burning_ship", w_len))
		return (4);
	return (0);
}

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
	else if (fractal_type == 4)
	{
		zoom.kx = 4.0 / WINDOW_WIDTH;
		zoom.ky = 3.0 / WINDOW_HEIGHT;
	}
	else
	{
		zoom.kx = 4.0 / WINDOW_WIDTH;
		zoom.ky = 4.0 / WINDOW_HEIGHT;
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
		cmplx.x = fractal.z_const.x;
		cmplx.y = fractal.z_const.y;
	}
	else if (fractal.fractal_type == 2 && argc < 5)
	{
		cmplx.x = ft_atof(argv[2]);
		cmplx.y = ft_atof(argv[3]);
		printf("During %f %f\n", cmplx.x, cmplx.y);
	}
	else
		cmplx = ft_initialize_coord();
	return (cmplx);
}
