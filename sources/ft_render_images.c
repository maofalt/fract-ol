/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/19 18:02:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_render(t_data *data)
{
	t_fractal	*fractal;

	if (data->win_ptr == NULL)
		return (1);
	ft_render_background(&data->img, WHITE_PIXEL);
	fractal = ft_initialize_fractal();
	if (!fractal)
		return (1);
	ft_render_fractal(&data->img, fractal);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}

void	ft_render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

int	ft_render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	ft_render_fractal(t_img *img, t_fractal *fractal)
{
	size_t			i;
	size_t			px;
	size_t			py;

	px = 0;
	while (px < WINDOW_WIDTH)
	{
		py = 0;
		while (py < WINDOW_HEIGHT)
		{
			/*Offset values to be calculated automatically so if Aspect ratio changes the image remains centered*/
			fractal->px_coord.x = -2 + (px / fractal->zoom.kx);
			fractal->px_coord.y = -1.25 + (py / fractal->zoom.ky);
			fractal->w = 0;
			fractal->polar_coord = ft_initialize_coord();
			fractal->sq_coord = ft_initialize_coord();
			i = 0;
			while ((fractal->sq_coord.x + fractal->sq_coord.y <= 4)
				&& (i < fractal->max_iter))
			{
				fractal->polar_coord.y = ((fractal->polar_coord.x + fractal->polar_coord.x) * fractal->polar_coord.y) + fractal->px_coord.y;
				fractal->polar_coord.x = fractal->sq_coord.x - fractal->sq_coord.y + fractal->px_coord.x;
				fractal->sq_coord.x = fractal->polar_coord.x * fractal->polar_coord.x;
				fractal->sq_coord.y = fractal->polar_coord.y * fractal->polar_coord.y;
				fractal->w = (fractal->polar_coord.x + fractal->polar_coord.y) * (fractal->polar_coord.x + fractal->polar_coord.y);
				i++;
			}
			if (i == fractal->max_iter)
				img_pix_put(img, px, py, BLACK_PIXEL);
			else
				img_pix_put(img, px, py, WHITE_PIXEL);
			py++;
		}
		px++;
	}
	return (0);
}