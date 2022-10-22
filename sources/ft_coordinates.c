/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coordinates.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/22 17:31:41 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

t_coord	ft_initialize_coord(void)
{
	t_coord	coord;

	coord.x = 0;
	coord.y = 0;
	return (coord);
}

t_zoom	ft_initialize_zoom(size_t fractal_type)
{
	t_zoom	zoom;

	if (fractal_type == 1)
	{
		zoom.kx = WINDOW_WIDTH / 2.47;
		zoom.ky = WINDOW_HEIGHT / 2.24;
	}
	else if (fractal_type == 2)
	{
		zoom.kx = WINDOW_WIDTH / 4;
		zoom.ky = WINDOW_HEIGHT / 4;
	}
	return (zoom);
}
