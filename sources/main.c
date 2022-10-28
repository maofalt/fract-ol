/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 22:40:23 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>


size_t	ft_fractal_type(int argc, char **argv)
{
	size_t	w_len;

	w_len = ft_strlen(argv[1]);
	if (!ft_strncmp(argv[1], "mandelbrot", w_len))
	{
		if (argc == 2 || (argc == 3 && argv[2][0] == '1'))
			return (1);
		if (argc == 2 || (argc == 3 && argv[2][0] == '2'))
			return (3);
	}
	else if (!ft_strncmp(argv[1], "julia", w_len))
		return (2);
	else if (!ft_strncmp(argv[1], "burning_ship", w_len))
		return (4);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc == 1)
	{
		ft_printf("Launch ./fractol with the following arguments \n1- ./fractol [fractal_type] [Real part of complexe] [Imaginary part of complexe]\n\nFractal types available: - mandelbrot | julia\nReal and imaginary part of complexe only available for mandelbrot\n\ne.g.: ./fractol julia 0.5 -0.365  ");
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
			mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &ft_handle_boutonpress, &data);
			mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &ft_handle_keypress, &data);
			mlx_hook(data.win_ptr, 17, 0L, &ft_destroy_window, &data);
			mlx_key_hook(data.win_ptr, &ft_handle_keyrelease, &data);
			mlx_loop(data.mlx_ptr);
		}
		free(data.fractal->palette);
		free(data.fractal);
		mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (0);
	}
	return (1);
}

/* Function parsing which type of fractal we are going to work with : **
** 1- "mandelbrot" as argument only or **
** 2- "mandelbrot" + '1' or '2'  **
** 3- "julia" without arguments or **
** 4- "julia" + two doubles representing Z.real + I*Z.imaginary **
** 5 - "burning_ship" without arguments */
int	ft_valid_argument(int argc, char **argv)
{
	size_t	w_len;

	if ((argc > 1) && (argc < 5))
	{
		w_len = ft_strlen(argv[1]);
		if (!(ft_strncmp(argv[1], "mandelbrot", w_len))
			&& (argc > 2 || argc < 3))
			return (1);
		else if (!(ft_strncmp(argv[1], "julia", w_len)))
		{
			if (argc == 2)
				return (1);
			else if (argc == 4 && ft_valid_d(argv[2]) && ft_valid_d(argv[3]))
				return (1);
			else
				return (0);
		}
		else if (!(ft_strncmp(argv[1], "burning_ship", w_len)) && (argc == 2))
			return (4);
	}
	return (0);
}

/* Validate for Julia fractals that the complexe form argumnts are valid,**
**  each character must be **
** 1- A digit (0 - 9) **
** 2 - Character '.' or '-' */
int	ft_valid_d(char *str)
{
	int	c;

	c = *str;
	while (*str++)
	{
		if (!(ft_isdigit(c) || c == '-' || c == '.'))
			return (0);
		c = *str;
	}
	return (1);
}
