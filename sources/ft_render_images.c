/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/22 23:00:14 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	//mlx_do_sync(data->mlx_ptr);
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
	size_t			px;
	size_t			py;

	px = 0;
	while (px < WINDOW_WIDTH)
	{
		py = 0;
		while (py < WINDOW_HEIGHT)
		{
			if (fractal->fractal_type == 1)
				ft_calculate_mandelbrot(img, fractal, px, py);
			else if (fractal->fractal_type == 2)
				ft_calculate_julia(img, fractal, px, py);
			py++;
		}
		px++;
	}
	printf("Fractal calulated!\n");
	return (0);
}
