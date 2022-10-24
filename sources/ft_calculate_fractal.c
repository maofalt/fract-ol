/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/24 14:25:08 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

/* for each pixel (Px, Py) on the screen do
    x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
    y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
    x := 0.0
    y := 0.0
	x2:= 0
	y2:= 0
	w:= 0
    iteration := 0
    max_iteration := 1000
    while (x2 + y2 ≤ 4 and iteration < max_iteration) do
		x:= x2 - y2 + x0
		y:= w - x2 - y2 + y0
		x2:= x × x
		y2:= y × y
		w:= (x + y) × (x + y)
		iteration:= iteration + 1
 
    color := palette[iteration]
    plot(Px, Py, color)*/

/* Create a vector a + ib with a Re and Im component it zill save up to 1 variable here*/

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

void	ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py)
{
	size_t	i;
	/*Offset values to be calculated automatically so if Aspect ratio changes the image remains centered*/
	fractal->px_coord.x = fractal->offset.x + (px * fractal->zoom.kx);
	fractal->px_coord.y = fractal->offset.y - (py * fractal->zoom.ky);
	fractal->w = 0;
	fractal->polar_coord = fractal->z_const;
	fractal->sq_coord = ft_initialize_coord();
	i = 0;
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
	//img_pix_put(img, px, py, i << 2);
	float temp = ((double)i / fractal->max_iter) * 5;
	if (temp > 1.0f)
		temp = 1.0f;
	else if (temp < 0.0f)
		temp = 0.0f;
	int oue = temp * 255;
	uint32_t col = (oue << 16) | (oue << 8) | oue;
	img_pix_put(img, px, py, col);
}


// 	/*Offset values to be calculated automatically so if Aspect ratio changes the image remains centered*/
// 	fractal->px_coord.x = fractal->offset.x + (px / fractal->zoom.kx);
// 	fractal->px_coord.y = fractal->offset.y + (py / fractal->zoom.ky);
// 	fractal->w = 0;
// 	fractal->polar_coord = ft_initialize_coord();
// 	fractal->polar_der = ft_initialize_coord();
// 	fractal->sq_coord = ft_initialize_coord();
// 	i = 0;
// 	while ((fractal->sq_coord.x + fractal->sq_coord.y <= 4)
// 		&& (i < fractal->max_iter))
// 	{
// 		i++;
// 	}
// 	img_pix_put(img, px, py, i << 2);
// }

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
	float temp = ((double)i / fractal->max_iter) * 5;
	if (temp > 1.0f)
		temp = 1.0f;
	else if (temp < 0.0f)
		temp = 0.0f;
	int oue = temp * 255;
	uint32_t col = (oue << 16) | (oue << 8) | oue;
	img_pix_put(img, px, py, col);
}
