/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/30 12:28:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc == 1)
		ft_error_message();
	else if (ft_valid_argument(argc, argv))
	{
		if (ft_mlx_start(&data))
			return (1);
		data.fractal = ft_initialize_fractal(argv, argc);
		if (!(&data.fractal))
			ft_destroy_window(&data);
		else if ((mlx_loop_hook(data.mlx_ptr, &ft_render, &data)))
			ft_mlx_engine(&data);
		ft_free_all(&data);
	}
	return (0);
}

/*destroy window ptr, mlx img ptr , free palette str, fractal structure**
** and destoy display*/
void	ft_free_all(t_data *data)
{
	free(data->fractal->palette);
	free(data->fractal);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

/* Function parsing which type of fractal we are going to work with : **
** 1- "mandelbrot" as argument only or **
** 2- "mandelbrot" + '1' or '2'  **
** 3- "julia" without arguments or **
** 4- "julia" + two doubles representing Z.real + I*Z.imaginary **
** 5 - "burning_ship" without arguments */
int	ft_valid_argument(int argc, char **argv)
{
	if ((argc > 1) && (argc < 5))
	{
		if ((ft_strcmp(argv[1], "mandelbrot"))
			&& (argc > 2 || argc < 3))
			return (1);
		else if ((ft_strcmp(argv[1], "julia")))
		{
			if (argc == 2)
				return (1);
			else if (argc == 4 && ft_valid_d(argv[2]) && ft_valid_d(argv[3]))
				return (1);
			else
				return (0);
		}
		else if ((ft_strcmp(argv[1], "burning_ship")) && (argc == 2))
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
	int		c;
	int		b;

	b = 0;
	c = *str;
	while (*str)
	{
		if (!(ft_isdigit(c) || c == '-' || c == '.'))
			return (0);
		b = *str++;
		c = *str;
		if (b == '.' && c == '-')
			return (0);
		if (b == '-' && c == '.')
			return (0);
	}
	return (1);
}

/*Set of instructions to use ./fractal program*/
void	ft_error_message(void)
{
	ft_printf("Launch ./fractol with the following arguments");
	ft_printf(" \n1- ./fractol [fractal_type] [Real part of complexe]");
	ft_printf("[Imaginary part of complexe]\n\n");
	ft_printf("Fractal types available: - mandelbrot | julia| burning ship");
	ft_printf("\nReal and imaginary part of complexe only available for ");
	ft_printf("julia\n\te.g.: ./fractol julia 0.5 -0.365 \n");
	ft_printf("\n\t============= CONTROLS ==============\n");
	ft_printf("\t|FOR ALL FRACTAL EXCEPT MANDELBROT 2\n\n");
	ft_printf("\t|-KEYBOARD-|----------EFFECT---------\n");
	ft_printf("\t|  ' - '   | DECREASE MAX ITERATIONS\n");
	ft_printf("\t|  ' + '   | INCREASE MAX ITERATIONS\n");
	ft_printf("\t|  ' [ '   | DECREASE ESCAPE RADIUS\n");
	ft_printf("\t|  ' ] '   | INCREASE ESCAPE RADIUS\n");
	ft_printf("\t| 1-6 (pad)| COLOR PROFILS FOR MANDELBROT\n");
	ft_printf("\t| 1-5 (pad)| COLOR PROFILS FOR OTHER FRACTALS\n\n");
	ft_printf("\t|============================================\n");
	ft_printf("\t|FOR ALL FRACTAL EXCEPT MANDELBROT 2 ON COLOR 5\n\n");
	ft_printf("\t|' - '(pad)| ITERATE THROUGHT COLORS\n");
	ft_printf("\t|' + '(pad)| ITERATE THROUGHT COLORS\n");
	ft_printf("\t|============================================\n");
	ft_printf("\t|\t\tFOR MANDELBROT 2\n\n");
	ft_printf("\t|  ' z '   | ROTATE CLOCKWISE SHADOW\n");
	ft_printf("\t|  ' x '   | ROTATE ANTICLOCKWISE SHADOW\n");
	ft_printf("\t|  ' f '   | INCREASE HIGH LIGHT SOURCE\n");
	ft_printf("\t|  ' v '   | DECREASE HIGH LIGHT SOURCE\n");
}
