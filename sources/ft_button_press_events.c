/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button_press_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 16:21:40 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

void	ft_destroy_window_button(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
}

	/* Events catching movements and moving into the fractal window*/
void	ft_movements_keys(int keysym, t_data *data)
{
	t_fractal	*fractal;
	double		delta;
	double		sign;

	sign = 1.0;
	if (keysym == UP_KEY || keysym == RIGHT_KEY)
		sign = -1.0 * sign;
	fractal = data->fractal;
	delta = (fractal->xtrm.im_max - fractal->xtrm.im_min) * 0.1;
	if (keysym == UP_KEY || keysym == DOWN_KEY)
	{
		fractal->xtrm.im_max = fractal->xtrm.im_max + (sign * delta);
		fractal->xtrm.im_min = fractal->xtrm.im_min + (sign * delta);
	}
	else if (keysym == RIGHT_KEY || keysym == LEFT_KEY)
	{
		fractal->xtrm.re_max = fractal->xtrm.re_max + (sign * delta);
		fractal->xtrm.re_min = fractal->xtrm.re_min + (sign * delta);
	}
	fractal->zoom.kx = (fractal->xtrm.re_max - fractal->xtrm.re_min)
		/ WINDOW_WIDTH;
	fractal->zoom.ky = (fractal->xtrm.im_max - fractal->xtrm.im_min)
		/ WINDOW_HEIGHT;
	fractal->offset.x = fractal->xtrm.re_min;
	fractal->offset.y = fractal->xtrm.im_max;
}

	/* ']' & ']' alllow us to cycle the color palette*/
void	ft_rotate_palette(int keysym, t_data *data)
{
	t_fractal	*fractal;
	double		sign;

	sign = 1.0;
	if (keysym == MINUS_PAD)
		sign = -1.0 * sign;
	fractal = data->fractal;
	fractal->palette[0] = (fractal->palette[0] + (sign * 0x1FEFE));
	fractal->palette[1] = (fractal->palette[1] + (sign * 0x000005));
	fractal->palette[2] = (fractal->palette[2] + (sign * 0x000006));
	fractal->palette[3] = (fractal->palette[3] + (sign * 0x000002));
	fractal->palette[4] = (fractal->palette[4] + (sign * 0x000003));
	fractal->palette[5] = (fractal->palette[5] + (sign * 0x000110));
	fractal->palette[6] = (fractal->palette[6] + (sign * 0x00F010));
	fractal->palette[7] = (fractal->palette[7] + (sign * 0xF00010));
	fractal->palette[8] = (fractal->palette[8] + (sign * 0x005010));
}
