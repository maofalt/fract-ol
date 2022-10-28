/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 01:17:33 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

/*Hooks (boutton press, button reease, destoy window,**
** key release and mxloop here)*/
void	ft_mlx_engine(t_data *data)
{
	mlx_hook(data->win_ptr, ButtonPress, ButtonPressMask,
		&ft_handle_boutonpress, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &ft_handle_keypress, data);
	mlx_hook(data->win_ptr, 17, 0L, &ft_destroy_window, data);
	mlx_key_hook(data->win_ptr, &ft_handle_keyrelease, data);
	mlx_loop(data->mlx_ptr);
}

	/*engine start and alloc mlxpt, win ptr  and img*/
int	ft_mlx_start(t_data *data)
{
		data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fract-ol");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		return (MLX_ERROR);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img.mlx_img == NULL)
	{
		free(data->mlx_ptr);
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
	return (0);
}
