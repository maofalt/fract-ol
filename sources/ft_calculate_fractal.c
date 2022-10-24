/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/24 16:55:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

t_fractal	*ft_initialize_fractal(char **argv, int argc)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->fractal_type = ft_fractal_type(argv);
	fractal->px_coord = ft_initialize_coord();
	fractal->polar_coord = ft_initialize_complexe(*fractal, argv, argc);
	fractal->z_const = ft_initialize_complexe(*fractal, argv, argc);
	fractal->sq_coord = ft_initialize_coord();
	fractal->xtrm = ft_initialize_extremes(fractal->fractal_type);
	fractal->zoom = ft_initialize_zoom(fractal->fractal_type);
	fractal->offset = ft_initialize_offset(fractal->fractal_type);
	fractal->w = 0;
	fractal->max_iter = 64;
	return (fractal);
}

uint32_t	ft_color_fractal(t_fractal *fractal, size_t i)
{
	uint32_t	color;
	float		temp;
	int			shift;

	temp = ((double)i / fractal->max_iter) * 5;
	if (temp > 1.0f)
		temp = 1.0f;
	else if (temp < 0.0f)
		temp = 0.0f;
	shift = temp * 255;
	color = (shift << 16) | (shift << 8) | shift;
	return (color);
}

// void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
// {
// 	size_t	i;

// 	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
// 	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
// 	fractal->w = 0;
// 	fractal->polar_coord = fractal->z_const;
// 	fractal->sq_coord = ft_initialize_coord();
// 	i = 0;
// 	while ((fractal->sq_coord.x + fractal->sq_coord.y <= 4)
// 		&& (i < fractal->max_iter))
// 	{
// 		fractal->polar_coord.y = ((2.0 * fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
// 		fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
// 		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
// 		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
// 		fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
// 		i++;
// 	}
// 	//img_pix_put(img, px, py, i << 2);
// 	img_pix_put(img, px, py, ft_color_fractal(fractal, i));
// }

void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t	i;
	double	log_zn;
	double	nu;
	int 	color, color1, color2;

	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord = fractal->z_const;
	fractal->sq_coord = ft_initialize_coord();
	i = 0;
	nu = 0;
	while ((fractal->sq_coord.x + fractal->sq_coord.y <= (1 << 16))
		&& (i < fractal->max_iter))
	{
		fractal->polar_coord.y = ((2.0 * fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
		fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
		fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
		i++;
	}
	if (i < fractal->max_iter)
	{
		log_zn = log(fractal->sq_coord.x + fractal->sq_coord.y) / 2;
		nu = log(log_zn / log(2)) / log(2);
		i = i + 1 - nu;
	}
	/*Deine what palette is*/
	color1 = palette[floor(iteration)];
	color2 = palette[floor(iteration) + 1];
	/*Define our lineare interpolation as seen in the exercce*/
	color = linear_interpolate(color1, color2, iteration % 1);
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
	while (((fractal->sq_coord.x + fractal->sq_coord.y) < 4)
		&& (i < fractal->max_iter))
	{
		fractal->w = (fractal->px_coord.x * fractal->px_coord.x) - (fractal->px_coord.y * fractal->px_coord.y);
		fractal->px_coord.y = (2 * fractal->px_coord.x * fractal->px_coord.y) + fractal->polar_coord.y;
		fractal->px_coord.x = fractal->w + fractal->polar_coord.x;
		fractal->sq_coord.x = fractal->px_coord.x * fractal->px_coord.x;
		fractal->sq_coord.y = fractal->px_coord.y * fractal->px_coord.y;;
		i++;
	}
	img_pix_put(img, px, py, ft_color_fractal(fractal, i));
}
