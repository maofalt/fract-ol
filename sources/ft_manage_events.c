/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 15:48:39 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	ft_handle_keypress(int keysym, t_data *data)
{
	double		delta;
	t_fractal	*fractal;

	fractal = data->fractal;
	delta = fractal->xtrm.im_max - fractal->xtrm.im_min;
	ft_destroy_window_button(keysym, data);
	if (keysym == UP_KEY || keysym == LEFT_KEY || keysym == DOWN_KEY || keysym == RIGHT_KEY)
	{
		if (keysym == DOWN_KEY)
		{
			fractal->xtrm.im_max += delta * 0.05;
			fractal->xtrm.im_min += delta * 0.05;
		}
		else if (keysym == UP_KEY)
		{
			fractal->xtrm.im_max -= delta * 0.05;
			fractal->xtrm.im_min -= delta * 0.05;
		}
		else if (keysym == RIGHT_KEY)
		{
			fractal->xtrm.re_max -= delta * 0.05;
			fractal->xtrm.re_min -= delta * 0.05;
		}
		else if (keysym == LEFT_KEY)
		{
			fractal->xtrm.re_max += delta * 0.05;
			fractal->xtrm.re_min += delta * 0.05;
		}
		fractal->zoom.kx = (fractal->xtrm.re_max - fractal->xtrm.re_min) / WINDOW_WIDTH;
		fractal->zoom.ky = (fractal->xtrm.im_max - fractal->xtrm.im_min) / WINDOW_HEIGHT;
		fractal->offset.x = fractal->xtrm.re_min;
		fractal->offset.y = fractal->xtrm.im_max;
		fractal->update = 1;
	}
	if (keysym == MINUS_PAD || keysym == PLUS_PAD)
	{
		if (keysym == PLUS_PAD)
		{
			fractal->palette[0] = (fractal->palette[0] + 0x1FEFE);
			fractal->palette[1] = (fractal->palette[1] + 0x000005);
			fractal->palette[2] = (fractal->palette[2] + 0x000006);
			fractal->palette[3] = (fractal->palette[3] + 0x000002);
			fractal->palette[4] = (fractal->palette[4] + 0x000003);
			fractal->palette[5] = (fractal->palette[5] + 0x000110);
			fractal->palette[6] = (fractal->palette[6] + 0x00F010);
			fractal->palette[7] = (fractal->palette[7] + 0xF00010);
			fractal->palette[8] = (fractal->palette[8] + 0x005010);
		}
		else if (keysym == MINUS_PAD)
		{
			fractal->palette[0] = (fractal->palette[0] - 0x1FEFE);
			fractal->palette[1] = (fractal->palette[1] - 0x000005);
			fractal->palette[2] = (fractal->palette[2] - 0x000006);
			fractal->palette[3] = (fractal->palette[3] - 0x000002);
			fractal->palette[4] = (fractal->palette[4] - 0x000003);
			fractal->palette[5] = (fractal->palette[5] - 0x000110);
			fractal->palette[6] = (fractal->palette[6] - 0x00F010);
			fractal->palette[7] = (fractal->palette[7] - 0xF00010);
			fractal->palette[8] = (fractal->palette[8] - 0x005010);
		}
		fractal->update = 1;
	}
	if (keysym == BRACE_L_KEY)
		fractal->r /= 2.0;
	if (keysym == BRACE_R_KEY)
		fractal->r *= 2.0;	
	if (keysym == MINUS_KEY)
		fractal->max_iter -= 10;
	if (keysym == PLUS_KEY)
		fractal->max_iter += 10;
	if (keysym == ONE_PAD)
	{
		fractal->color_method = 1;
		if (fractal->fractal_type == 3)
			fractal->fractal_type = 1;
	}
	else if (keysym == TWO_PAD)
	{
		if (fractal->fractal_type == 3)
			fractal->fractal_type = 1;
		fractal->color_method = 2;
	}	
	else if (keysym == THREE_PAD)
	{
		if (fractal->fractal_type == 3)
			fractal->fractal_type = 1;
		fractal->color_method = 3;
	}
	else if (keysym == FOUR_PAD)
	{
		if (fractal->fractal_type == 3)
			fractal->fractal_type = 1;
		fractal->color_method = 4;
	}
	else if (keysym == FIVE_PAD)
	{
		if (fractal->fractal_type == 3)
			fractal->fractal_type = 1;
		fractal->color_method = 5;
	}
	else if (keysym == SIX_PAD && fractal->fractal_type == 1)
		fractal->fractal_type = 3;
	if (keysym == X_KEY || keysym == Z_KEY)
	{
		if (keysym == X_KEY)
			fractal->angle -= 3;
		if (keysym == Z_KEY)
			fractal->angle += 3;
	}
	if (keysym == D_KEY || keysym == C_KEY)
	{
		if (keysym == D_KEY)
			fractal->h += 0.1;
		if (keysym == C_KEY)
			fractal->h -= 0.1;
	}
	fractal->update = 1;
	printf("%d\n",keysym);
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
	}	
	else if (buttonsym == 5)
	{
		delta_derr = ((1 / scalefactor) * delta_re) - delta_re;
		delta_deri = ((1 / scalefactor) * delta_im) - delta_im;
	}
	else if (buttonsym == 1)
	{
		data->fractal->z_const.x = data->fractal->offset.x + (x * data->fractal->zoom.kx);
		data->fractal->z_const.y = data->fractal->offset.y - (y * data->fractal->zoom.ky);
		data->fractal->fractal_type = 2;
		data->fractal->xtrm = ft_initialize_extremes(2);
		data->fractal->offset = ft_initialize_offset(2);
		data->fractal->zoom = ft_initialize_zoom(2);	
	}	
	data->fractal->xtrm.re_min = data->fractal->xtrm.re_min - (delta_derr * xRatio);
	data->fractal->xtrm.re_max = data->fractal->xtrm.re_max + (delta_derr * (1 - xRatio));
	data->fractal->xtrm.im_max = data->fractal->xtrm.im_max + (delta_deri * yRatio);
	data->fractal->xtrm.im_min = data->fractal->xtrm.im_min - (delta_deri * (1 - yRatio));
	data->fractal->zoom.kx = (data->fractal->xtrm.re_max - data->fractal->xtrm.re_min) / WINDOW_WIDTH;
	data->fractal->zoom.ky = (data->fractal->xtrm.im_max - data->fractal->xtrm.im_min) / WINDOW_HEIGHT;
	data->fractal->offset.x = data->fractal->xtrm.re_min;
	data->fractal->offset.y = data->fractal->xtrm.im_max;
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
