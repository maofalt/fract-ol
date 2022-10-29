/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_button_press_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/30 00:08:45 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

t_coord	ft_button_press_zoom(int buttonsym, t_coord delta)
{
	double		scalefactor;
	t_coord		delta_der;

	scalefactor = 1 / 1.1;
	if (buttonsym == 4)
	{
		delta_der.x = (scalefactor * delta.x) - delta.x;
		delta_der.y = (scalefactor * delta.y) - delta.y;
	}	
	else if (buttonsym == 5)
	{
		delta_der.x = ((1 / scalefactor) * delta.x) - delta.x;
		delta_der.y = ((1 / scalefactor) * delta.y) - delta.y;
	}
	else
		delta_der = ft_initialize_coord();
	return (delta_der);
}

void	ft_equivalent_julia(t_fractal *fractal, int x, int y, int buttonsym)
{
	if (buttonsym == 1 && fractal->fractal_type != 4)
	{
		fractal->z_const.x = fractal->offset.x + (x * fractal->zoom.kx);
		fractal->z_const.y = fractal->offset.y - (y * fractal->zoom.ky);
		fractal->fractal_type = 2;
		fractal->xtrm = ft_initialize_extremes(2);
		fractal->offset = ft_initialize_offset(2);
		fractal->zoom = ft_initialize_zoom(2);
	}
}
