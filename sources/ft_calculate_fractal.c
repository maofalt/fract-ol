/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/19 17:17:05 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

/* for each pixel (Px, Py) on the screen do
    x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
    y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
    x := 0.0
    y := 0.0
	x2:= 0
	y2:= 0
	w:= 0
    iteration := 0
    max_iteration := 1000
    while (x2 + y2 ≤ 4 and iteration < max_iteration) do
		x:= x2 - y2 + x0
		y:= w - x2 - y2 + y0
		x2:= x × x
		y2:= y × y
		w:= (x + y) × (x + y)
		iteration:= iteration + 1
 
    color := palette[iteration]
    plot(Px, Py, color)*/

/* Create a vector a + ib with a Re and Im component it zill save up to 1 variable here*/

t_fractal	*ft_initialize_fractal(void)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (NULL);
	fractal->px_coord = ft_initialize_coord();
	fractal->polar_coord = ft_initialize_coord();
	fractal->sq_coord = ft_initialize_coord();
	fractal->zoom = ft_initialize_zoom();
	fractal->w = 0;
	fractal->max_iter = 100;
	return (fractal);
}
