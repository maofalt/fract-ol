/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 18:53:31 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

t_fractal	*ft_initialize_fractal(char **argv, int argc)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->fractal_type = ft_initialize_fractal_type(argc, argv);
	fractal->px_coord = ft_initialize_coord();
	fractal->polar_coord = ft_initialize_complexe(*fractal, argv, argc);
	fractal->z_const = ft_initialize_complexe(*fractal, argv, argc);
	fractal->sq_coord = ft_initialize_coord();
	fractal->xtrm = ft_initialize_extremes(fractal->fractal_type);
	fractal->zoom = ft_initialize_zoom(fractal->fractal_type);
	fractal->offset = ft_initialize_offset(fractal->fractal_type);
	fractal->w = 0;
	fractal->max_iter = 200;
	fractal->update = 1;
	fractal->color_method = 1;
	fractal->palette = ft_intialize_palette();
	fractal->angle = 45.0;
	fractal->h = 1.5;
	fractal->r = 2.0;
	return (fractal);
}


void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t				i;
	double				period;
	double			v_real = cos(2.0 * fractal->angle * PI / 360.0);
	double			v_img = sin(2.0 * fractal->angle * PI /360.0);
	t_coord 		dc;
	t_coord			u = ft_initialize_coord();
	double			q = 0;
	double			t = 0;
	double			tmp;

	dc = ft_initialize_coord();
	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord = fractal->z_const;
	fractal->sq_coord = ft_initialize_coord();
	fractal->old = ft_initialize_coord();
	period = 0;
	i = 0;
	if (ft_check_shapes(img, fractal, px, py))
		return ;
	while ((fractal->sq_coord.x + fractal->sq_coord.y <= fractal->r * fractal->r)
		&& (i < fractal->max_iter))
	{
		tmp = dc.x;
		dc.x = (2.0 * ((dc.x *  fractal->polar_coord.x) - (dc.y *  fractal->polar_coord.y)))+ 1.0;
		dc.y=  2.0 * ((tmp* fractal->polar_coord.y) + (dc.y * fractal->polar_coord.x));
		fractal->polar_coord.y = ((2.0 * fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
		fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
		fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
		i++;
		if (ft_check_period(fractal, &period, &i))
			break ;
	}
	if (fractal->fractal_type == 3)
	{
		if (i == fractal->max_iter)
		{
			img_pix_put(img, px, py, encode_rgb(1, 0,0,0));
		}
		else
		{
			q = (dc.x * dc.x) + (dc.y * dc.y);
			u.x = ((fractal->polar_coord.x * dc.x) + (fractal->polar_coord.y * dc.y)) / q;
			u.y = ((fractal->polar_coord.y * dc.x) - (fractal->polar_coord.x * dc.y)) / q;
			q = sqrt((u.x * u.x) + (u.y * u.y));
			u.x = u.x / q;
			u.y = u.y / q;
			t = (u.x * v_real) + (u.y * v_img) + fractal->h;
			t = t / (1.0 + fractal->h);
			if (t < 0.0)
				t = 0.0;
			img_pix_put(img, px, py, encode_rgb(1, 255 * t, 255 * t, 255 * t));
		}
	}
	else
		img_pix_put(img, px, py, ft_color_fractal(fractal, i));
}

void	ft_calculate_julia(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t	i;

	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord = fractal->z_const;
	fractal->sq_coord = ft_initialize_coord();
	i = 0;
	while (((fractal->sq_coord.x + fractal->sq_coord.y) < fractal->r *fractal->r)
		&& (i < fractal->max_iter))
	{
		fractal->w = (fractal->px_coord.x * fractal->px_coord.x) - (fractal->px_coord.y * fractal->px_coord.y);
		fractal->px_coord.y = (2 * fractal->px_coord.x * fractal->px_coord.y) + fractal->polar_coord.y;
		fractal->px_coord.x = fractal->w + fractal->polar_coord.x;
		fractal->sq_coord.x = fractal->px_coord.x * fractal->px_coord.x;
		fractal->sq_coord.y = fractal->px_coord.y * fractal->px_coord.y;
		i++;
	}
	img_pix_put(img, px, py, ft_color_fractal(fractal, i));
}

void	ft_calculate_burning_ship(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t	i;

	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord.x = fractal->px_coord.x;
	fractal->polar_coord.y = fractal->px_coord.y;
	fractal->sq_coord.x = (fractal->polar_coord.x * fractal->polar_coord.x);
	fractal->sq_coord.y = (fractal->polar_coord.y * fractal->polar_coord.y);
	fractal->old = ft_initialize_coord();
	i = 0;
	while ((fractal->sq_coord.x + fractal->sq_coord.y < fractal->r * fractal->r)
		&& (i < fractal->max_iter))
	{
		fractal->w = (fractal->polar_coord.x * fractal->polar_coord.x) - (fractal->polar_coord.y * fractal->polar_coord.y) + fractal->px_coord.x;
		fractal->polar_coord.y = (2 * fractal->polar_coord.x * fractal->polar_coord.y) * (2 * fractal->polar_coord.x * fractal->polar_coord.y);
		fractal->polar_coord.y = sqrt(fractal->polar_coord.y) + fractal->px_coord.y;
		fractal->polar_coord.x = fractal->w;
		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
		i++;
	}
	img_pix_put(img, px, WINDOW_WIDTH - py, ft_color_fractal(fractal, i));
}