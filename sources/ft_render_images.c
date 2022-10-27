/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/27 23:08:43 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (data->fractal->update)
	{
		ft_render_fractal(&data->img, data->fractal);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.mlx_img, 0, 0);
		data->fractal->update = 0;
	}
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

// int	ft_render_fractal(t_img *img, t_fractal *fractal)
// {
// 	size_t			px;
// 	size_t			py = 0;
// 	size_t			ymin = 0;
// 	size_t			ymax = WINDOW_HEIGHT;

// 	if (fractal->fractal_type == 1)
// 	{
// 		if (fractal->xtrm.im_min < 0 && fractal->xtrm.im_max > 0)
// 		{
// 			if (fractal->xtrm.im_max + fractal->xtrm.im_min >= 0)
// 				ymax = ((fractal->xtrm.im_max * WINDOW_HEIGHT) / (fractal->xtrm.im_max - fractal->xtrm.im_min)) + 1;
// 			else
// 				ymin = ((fractal->xtrm.im_max * WINDOW_HEIGHT) / (fractal->xtrm.im_max - fractal->xtrm.im_min));
// 		}
// 	}
// 	else if (fractal->fractal_type == 2)
// 	{
// 		ymin = 0;
// 		ymax = WINDOW_HEIGHT;
// 	}
// 	py = ymin;
// 	while (py <= ymax)
// 	{
// 		px = 0;
// 		while (px < WINDOW_WIDTH)
// 		{
// 			if (fractal->fractal_type == 1)
// 				ft_calculate_mandelbrot(img, fractal, px, py);
// 			else if (fractal->fractal_type == 2)
// 				ft_calculate_julia(img, fractal, px, py);
// 			px++;
// 		}
// 		py++;
// 	}
// 	if (fractal->fractal_type == 1)
// 	{
// 		py = 0;
// 		while (py <= ymin)
// 		{
// 			ft_memcpy(img->addr + ((py) * img->line_len), img->addr + (img->line_len * (2 * ymin - py)), img->line_len);
// 			py++;
// 		}
// 		py = ymax;
// 		while (py <= WINDOW_HEIGHT)
// 		{
// 			ft_memcpy( img->addr + ((py) * img->line_len), img->addr + (img->line_len * (2 * ymax - py)), img->line_len);
// 			py++;
// 		}
// 	}
// 	printf("Fractal calulated!\n");
// 	return (0);
// }

int	ft_render_fractal(t_img *img, t_fractal *fractal)
{
	size_t			px;
	size_t			py = 0;
	size_t			ymin = 0;
	size_t			ymax = WINDOW_HEIGHT;

	if (fractal->fractal_type == 1)
	{
		if (fractal->xtrm.im_min < 0 && fractal->xtrm.im_max > 0)
		{
			if (fractal->xtrm.im_max + fractal->xtrm.im_min >= 0)
				ymax = ((fractal->xtrm.im_max * WINDOW_HEIGHT) / (fractal->xtrm.im_max - fractal->xtrm.im_min)) + 1;
			else
				ymin = ((fractal->xtrm.im_max * WINDOW_HEIGHT) / (fractal->xtrm.im_max - fractal->xtrm.im_min));
		}
	}
	else if (fractal->fractal_type == 2 || fractal->fractal_type == 3)
	{
		ymin = 0;
		ymax = WINDOW_HEIGHT;
	}
	py = ymin;
	while (py <= ymax)
	{
		px = 0;
		while (px < WINDOW_WIDTH)
		{
			if (fractal->fractal_type == 1 || fractal->fractal_type == 3)
				ft_calculate_mandelbrot(img, fractal, px, py);
			else if (fractal->fractal_type == 2)
				ft_calculate_julia(img, fractal, px, py);
			px++;
		}
		py++;
	}
	if (fractal->fractal_type == 1)
	{
		py = 0;
		while (py <= ymin)
		{
			ft_memcpy(img->addr + ((py) * img->line_len), img->addr + (img->line_len * (2 * ymin - py)), img->line_len);
			py++;
		}
		py = ymax;
		while (py <= WINDOW_HEIGHT)
		{
			ft_memcpy( img->addr + ((py) * img->line_len), img->addr + (img->line_len * (2 * ymax - py)), img->line_len);
			py++;
		}
	}
	printf("Fractal calulated!\n");
	return (0);
}