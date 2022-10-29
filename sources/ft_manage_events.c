/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 18:39:16 by motero           ###   ########.fr       */
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
	t_coord		delta;
	t_coord		delta_der;
	t_coord		ratio;
	t_fractal	*fractal;

	fractal = data->fractal;
	delta.x = fractal->xtrm.re_max - fractal->xtrm.re_min;
	delta.y = fractal->xtrm.im_max - fractal->xtrm.im_min;
	ratio.x = (double)x / WINDOW_WIDTH;
	ratio.y = (double)y / WINDOW_HEIGHT;
	delta_der = ft_button_press_zoom(buttonsym, delta);
	ft_equivalent_julia(fractal, x, y, buttonsym);
	fractal->xtrm.re_min = fractal->xtrm.re_min - (delta_der.x * ratio.x);
	fractal->xtrm.re_max = fractal->xtrm.re_max + (delta_der.x * (1 - ratio.x));
	fractal->xtrm.im_max = fractal->xtrm.im_max + (delta_der.y * ratio.y);
	fractal->xtrm.im_min = fractal->xtrm.im_min - (delta_der.y * (1 - ratio.y));
	fractal->zoom.kx = (fractal->xtrm.re_max - fractal->xtrm.re_min)
		/ WINDOW_WIDTH;
	fractal->zoom.ky = (fractal->xtrm.im_max - fractal->xtrm.im_min)
		/ WINDOW_HEIGHT;
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
