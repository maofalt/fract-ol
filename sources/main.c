/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/23 04:51:29 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue)
{
	return (hue << 24 | red << 16 | green << 8 | blue);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	ft_valid_argument(int argc, char **argv)
{
	size_t	w_len;

	if ((argc > 1) && (argc < 5))
	{
		w_len = ft_strlen(argv[1]);
		if (!(ft_strncmp(argv[1], "mandelbrot", w_len)) && argc == 2)
			return (1);
		else if (!(ft_strncmp(argv[1], "julia", w_len)))
		{
			/* Verify that argv[2 - 5] contain only numbers + - and .*/
			if (argc == 2 || argc < 3)
				return (1);
			else
				return (0);
		}		
	}
	return (0);
}

size_t	ft_fractal_type(char **argv)
{
	size_t	w_len;

	w_len = ft_strlen(argv[1]);
	if (!ft_strncmp(argv[1], "mandelbrot", w_len))
		return (1);
	else if (!ft_strncmp(argv[1], "julia", w_len))
		return (2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc == 1)
	{
		ft_printf("Input a fractal as argument");
	}
	else if (ft_valid_argument(argc, argv))
	{
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (MLX_ERROR);
		data.win_ptr = mlx_new_window(data.mlx_ptr,
				WINDOW_WIDTH, WINDOW_HEIGHT, "Fract-ol");
		if (data.win_ptr == NULL)
		{
			free(data.win_ptr);
			return (MLX_ERROR);
		}
		data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
		data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
				&data.img.line_len, &data.img.endian);
		data.fractal = ft_initialize_fractal(argv, argc);
		if (!data.fractal)
			;
		else if ((mlx_loop_hook(data.mlx_ptr, &ft_render, &data)))
		{
			ft_render_fractal(&data.img, data.fractal);
			mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &ft_handle_keypress, &data);
			mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &ft_handle_boutonpress, &data);
			mlx_key_hook(data.win_ptr, &ft_handle_keyrelease, &data);
			mlx_loop(data.mlx_ptr);
			/*free fractal structure*/
		}
		mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (0);
	}
	return (1);
}
