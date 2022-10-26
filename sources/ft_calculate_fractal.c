/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/26 14:56:13 by motero           ###   ########.fr       */
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
	fractal->update = 1;
	return (fractal);
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

uint32_t	ft_linear_interpolation(uint32_t color1, uint32_t color2, double temp)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	r1 = (color1 >> 16) & 0xff;
	uint8_t	r2 = (color2 >> 16) & 0xff;
	uint8_t	g1 = (color1 >> 8) & 0xff;
	uint8_t	g2 = (color2 >> 8) & 0xff;
	uint8_t	b1 = color1 & 0xff;
	uint8_t	b2 = color2 & 0xff;

	r = r1 +(r2 - r1) * temp;
	g = g1 +(g2 - g1) * temp;
	b = b1 +(b2 - b1) * temp;
	return (encode_rgb(1, r, g, b));
}

uint32_t	ft_color_fractal(t_fractal *fractal, double i)
{
	uint32_t		color = 0, color1 = 0, color2 = 0;
	double			temp;
	int				shift;
	size_t			color_method = 5;
	const size_t	color_max = 0x777777;
	uint32_t		palette[9] = {0x11b899, 0x57bc9c, 0x9dbf9e, 0xb7cbaa, 0xd0d6b5, 0xe5c6b1, 0xee7674, 0xf49690, 0xf9b5ac};
	double			log_zn;
	double			nu = 0;

	color = 0;
	if (color_method == 0)
	{	
		temp = ((double)i / fractal->max_iter) * 5;
		if (temp > 1.0f)
			temp = 1.0f;
		else if (temp < 0.0f)
			temp = 0.0f;
		shift = temp * 255;
		color = (shift << 16) | (shift << 8) | shift;
	}
	else if (color_method == 1 || color_method == 2 || color_method == 3)
	{
		temp = ((double)i / fractal->max_iter);
		if (color_method == 1)
			color = temp * (double)color_max;
		if (color_method == 2)
			color = ft_bernstein_interpolation(temp);
		if (color_method == 3)
			color = ft_linear_interpolation(palette[0], palette[1], temp);
	}
	else if (color_method == 4 || color_method == 5)
	{
		nu = i;
		if (floor(i) < fractal->max_iter)
		{
			log_zn = log(fractal->sq_coord.x + fractal->sq_coord.y) / 2;
			nu = i + 1 - log(log_zn / log(2)) / log(2);
		}
		else
			return (0x11b899);
		color1 = palette[(int)(nu) % 9];
		color2 = palette[((int)(nu) + 1) % 9];
		temp = nu - floor(nu);
	//	temp = fmod(i,1);
		if (color_method == 4)
			color = ft_bernstein_interpolation(temp);
		if (color_method == 5)
			color = ft_linear_interpolation(color1, color2, temp);
	}
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
// 	img_pix_put(img, px, py, ft_color_fractal(fractal, i));
// }

void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t	i;
	double	q;

	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord = fractal->z_const;
	fractal->sq_coord = ft_initialize_coord();
	i = 0;
	q = pow(fractal->px_coord.x - 0.25, 2) + (fractal->px_coord.y * fractal->px_coord.y);
	if (0.25 * fractal->px_coord.y * fractal->px_coord.y >= (q * (q + (fractal->px_coord.x - 0.25))) ||
		(pow(fractal->px_coord.x + 1, 2) + (fractal->px_coord.y * fractal->px_coord.y) <= (double)1/16))
	{
		img_pix_put(img, px, py, ft_color_fractal(fractal, fractal->max_iter));
		return ;
	}
	while ((fractal->sq_coord.x + fractal->sq_coord.y <= 4)
		&& (i < fractal->max_iter))
	{
		fractal->polar_coord.y = ((2.0 * fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
		fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
		fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
		i++;
	}
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
