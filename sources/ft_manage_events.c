/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/26 21:28:15 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_handle_keypress(int keysym, t_data *data)
{
	double delta = data->fractal->xtrm.im_max - data->fractal->xtrm.im_min;

	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == UP_KEY || keysym == LEFT_KEY || keysym == DOWN_KEY || keysym == RIGHT_KEY)
	{
		if (keysym == DOWN_KEY)
		{
			data->fractal->xtrm.im_max += delta * 0.05;
			data->fractal->xtrm.im_min += delta * 0.05;
		}
		else if (keysym == UP_KEY)
		{
			data->fractal->xtrm.im_max -= delta * 0.05;
			data->fractal->xtrm.im_min -= delta * 0.05;
		}
		else if (keysym == RIGHT_KEY)
		{
			data->fractal->xtrm.re_max -= delta * 0.05;
			data->fractal->xtrm.re_min -= delta * 0.05;
		}
		else if (keysym == LEFT_KEY)
		{
			data->fractal->xtrm.re_max += delta * 0.05;
			data->fractal->xtrm.re_min += delta * 0.05;
		}
		// printf("New Offset");
		// data->fractal->offset.x = data->fractal->xtrm.re_min;
		// data->fractal->offset.y = data->fractal->xtrm.im_max;
		// printf("New Offset x: %f y:%f\n",data->fractal->offset.x, data->fractal->offset.y);
		//ft_render_fractal(&data->img, data->fractal);
		printf("zoom X %f zoom Y %f\n",data->fractal->zoom.kx, data->fractal->zoom.kx);
		data->fractal->zoom.kx = (data->fractal->xtrm.re_max - data->fractal->xtrm.re_min) / WINDOW_WIDTH;
		data->fractal->zoom.ky = (data->fractal->xtrm.im_max - data->fractal->xtrm.im_min) / WINDOW_HEIGHT;
		data->fractal->offset.x = data->fractal->xtrm.re_min;
		data->fractal->offset.y = data->fractal->xtrm.im_max;
		data->fractal->update = 1;
	}
	return (0);
}

int	ft_destroy_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_data *data)
{
	double	delta_re = data->fractal->xtrm.re_max - data->fractal->xtrm.re_min;
	double	delta_im = data->fractal->xtrm.im_max - data->fractal->xtrm.im_min;
	double	delta_derr = 0, delta_deri = 0;
	double xRatio = (double)x / WINDOW_WIDTH;
	double yRatio = (double)y / WINDOW_HEIGHT;
	double	scalefactor = 1 / 1.1;

	if (buttonsym == 4)
	{
		delta_derr = (scalefactor * delta_re) - delta_re;
		delta_deri = (scalefactor * delta_im) - delta_im;
		data->fractal->max_iter += 5;
	}	
	else if (buttonsym == 5)
	{
		delta_derr = ((1 / scalefactor) * delta_re) - delta_re;
		delta_deri = ((1 / scalefactor) * delta_im) - delta_im;
		data->fractal->max_iter -= 5;
	}
	data->fractal->xtrm.re_min = data->fractal->xtrm.re_min - (delta_derr * xRatio);
	data->fractal->xtrm.re_max = data->fractal->xtrm.re_max + (delta_derr * (1 - xRatio));
	data->fractal->xtrm.im_max = data->fractal->xtrm.im_max + (delta_deri * yRatio);
	data->fractal->xtrm.im_min = data->fractal->xtrm.im_min - (delta_deri * (1 - yRatio));
	data->fractal->zoom.kx = (data->fractal->xtrm.re_max - data->fractal->xtrm.re_min) / WINDOW_WIDTH;
	data->fractal->zoom.ky = (data->fractal->xtrm.im_max - data->fractal->xtrm.im_min) / WINDOW_HEIGHT;
	data->fractal->offset.x = data->fractal->xtrm.re_min;
	data->fractal->offset.y = data->fractal->xtrm.im_max;
	printf("zoom X %f zoom Y %f\n",data->fractal->zoom.kx, data->fractal->zoom.kx);
	data->fractal->update = 1;
	return (0);
}

int	ft_handle_keyrelease(int keysym, t_data *data)
{
	(void)data;
	if (keysym == XK_Escape)
		printf("EScape released\n");
	return (0);
}
