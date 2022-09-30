/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/09/30 03:09:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MLX_ERROR 1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00

/* bpp = bits per pixel */
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;



/* The x and y coordinates of the rect corresponds to its upper left corner. */

int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	handle_keyrelease(int keysym, t_data *data)
{
	(void)data;
	if (keysym == XK_Escape)
	// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		printf("EScape released\n");
	return (0);
}

int	render(t_data *data)
{
	render_rect(data, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100,
		100, 100, GREEN_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});
	return (0);
}

// int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
// {
// 	return (red << 16 | green << 8 | blue);
// }

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_key_hook(data.win_ptr, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	//mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
