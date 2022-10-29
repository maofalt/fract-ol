/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 18:01:59 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_handle_keypress(int keysym, t_data *data)
{
	t_fractal	*fractal;

	fractal = data->fractal;
	ft_destroy_window_button(keysym, data);
	ft_movements_keys(keysym, data);
	ft_rotate_palette(keysym, data);
	ft_pad_numbers(keysym, data);
	ft_keyboard_press(keysym, data);
	fractal->update = 1;
	return (0);
}

int	ft_destroy_window(t_data *data)
{	
	free(data->fractal->palette);
	free(data->fractal);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(1);
	return (0);
}

int	ft_handle_boutonpress(int buttonsym, int x, int y, t_data *data)
{
	double		delta_re;
	double		delta_im;
	double		delta_derr;
	double		delta_deri;
	double		xRatio;
	double		yRatio;
	double		scalefactor;
	t_fractal	*fractal;

	fractal = data->fractal;
	delta_re = fractal->xtrm.re_max - fractal->xtrm.re_min;
	delta_im = fractal->xtrm.im_max - fractal->xtrm.im_min;
	delta_derr = 0;
	delta_deri = 0;
	xRatio = (double)x / WINDOW_WIDTH;
	yRatio = (double)y / WINDOW_HEIGHT;
	scalefactor = 1 / 1.1;
	if (buttonsym == 4)
	{
		delta_derr = (scalefactor * delta_re) - delta_re;
		delta_deri = (scalefactor * delta_im) - delta_im;
	}	
	else if (buttonsym == 5)
	{
		delta_derr = ((1 / scalefactor) * delta_re) - delta_re;
		delta_deri = ((1 / scalefactor) * delta_im) - delta_im;
	}
	else if (buttonsym == 1)
	{
		fractal->z_const.x = fractal->offset.x + (x * fractal->zoom.kx);
		fractal->z_const.y = fractal->offset.y - (y * fractal->zoom.ky);
		fractal->fractal_type = 2;
		fractal->xtrm = ft_initialize_extremes(2);
		fractal->offset = ft_initialize_offset(2);
		fractal->zoom = ft_initialize_zoom(2);	
	}	
	fractal->xtrm.re_min = fractal->xtrm.re_min - (delta_derr * xRatio);
	fractal->xtrm.re_max = fractal->xtrm.re_max + (delta_derr * (1 - xRatio));
	fractal->xtrm.im_max = fractal->xtrm.im_max + (delta_deri * yRatio);
	fractal->xtrm.im_min = fractal->xtrm.im_min - (delta_deri * (1 - yRatio));
	fractal->zoom.kx = (fractal->xtrm.re_max - fractal->xtrm.re_min) / WINDOW_WIDTH;
	fractal->zoom.ky = (fractal->xtrm.im_max - fractal->xtrm.im_min) / WINDOW_HEIGHT;
	fractal->offset.x = fractal->xtrm.re_min;
	fractal->offset.y = fractal->xtrm.im_max;
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
