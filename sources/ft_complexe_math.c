/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complexe_math.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 22:24:20 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Fractol.h>

void	ft_derivate_complex(t_fractal *fractal)
{
	double	tmp;

	tmp = fractal->dc.x;
	fractal->dc.x = (2.0 * ((fractal->dc.x * fractal->polar_coord.x)
				- (fractal->dc.y * fractal->polar_coord.y))) + 1.0;
	fractal->dc.y = (2.0 * ((tmp * fractal->polar_coord.y)
				+ (fractal->dc.y * fractal->polar_coord.x)));
}
