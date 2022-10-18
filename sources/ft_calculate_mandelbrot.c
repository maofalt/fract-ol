/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/18 19:29:55 by motero           ###   ########.fr       */
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
int	ft_cal_mandelbrot(t_img *img)
{
	double			x0;
	double			y0;
	double			w;
	double			x;
	double			y;
	double			x2;
	double			y2;
	double			kx;
	double			ky;
	size_t			max_iterations;
	size_t			i;
	size_t			px;
	size_t			py;

	kx = WINDOW_WIDTH / RE_MAX;
	ky = WINDOW_HEIGHT / IM_MAX;
	px = 0;
	while (px < WINDOW_WIDTH)
	{
		py = 0;
		while (py < WINDOW_HEIGHT)
		{
			x0 = -2 + px / kx;
			y0 = -1.25 + (py / ky);
			w = 0;
			x = 0;
			y = 0;
			x2 = 0;
			y2 = 0;
			i = 0;
			max_iterations = 1000;
			while ((x2 + y2 <= 4) && (i < max_iterations))
			{
				y = w - x2 - y2 + y0;
				x = x2 - y2 + x0;
				x2 = x * x;
				y2 = y * y;
				w = (x + y) * (x + y);
				i++;
			}
			if (i == max_iterations)
				img_pix_put(img, px, py, RED_PIXEL);
			else
				img_pix_put(img, px, py, BLACK_PIXEL);
			py++;
		}
		px++;
	}
	return (0);
}
