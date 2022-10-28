/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 23:20:03 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

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
	//	temp = fmod(i,1);
		if (fractal->color_method == 4)
			color = ft_bernstein_interpolation(temp);
		if (fractal->color_method == 5)
			color = ft_linear_interpolation(color1, color2, temp);
	}
	return (color);
}

int	ft_check_shapes(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	double	q;

	q = pow(fractal->px_coord.x - 0.25, 2) + (fractal->px_coord.y * fractal->px_coord.y);
	if (0.25 * fractal->px_coord.y * fractal->px_coord.y >= (q * (q + (fractal->px_coord.x - 0.25))) ||
		(pow(fractal->px_coord.x + 1, 2) + (fractal->px_coord.y * fractal->px_coord.y) <= (double)1/16))
	{
		if (fractal->fractal_type == 3)
			img_pix_put(img, px, py, 0x000000);
		else
			img_pix_put(img, px, py, ft_color_fractal(fractal, fractal->max_iter));
		return (1);
	}
	return (0);
}

int	ft_check_period(t_fractal *fractal, double *period, size_t *i)
{
	if (fractal->polar_coord.x == fractal->old.x && fractal->polar_coord.y == fractal->old.y)
	{
		*i = fractal->max_iter;
		return (1);
	}
	*period = *period + 1;
	if (*period > 4)
	{
		*period = 0;
		fractal->old.x = fractal->polar_coord.x;
		fractal->old.y = fractal->polar_coord.y;
	}
	return (0);
}

// void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
// {
// 	size_t	i;
// 	double	period;

// 	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
// 	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
// 	fractal->w = 0;
// 	fractal->polar_coord = fractal->z_const;
// 	fractal->sq_coord = ft_initialize_coord();
// 	fractal->old = ft_initialize_coord();
// 	period = 0;
// 	i = 0;
// 	if (ft_check_shapes(img, fractal, px, py))
// 		return ;
// 	while ((fractal->sq_coord.x + fractal->sq_coord.y <= 4)
// 		&& (i < fractal->max_iter))
// 	{
// 		fractal->polar_coord.y = ((2.0 * fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
// 		fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
// 		fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
// 		fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
// 		fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
// 		i++;
// 		if (ft_check_period(fractal, &period, &i))
// 			break ;
// 	}
// 	img_pix_put(img, px, py, ft_color_fractal(fractal, i));
// }

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