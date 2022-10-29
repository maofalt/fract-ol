/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complexe_math.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/30 00:28:29 by motero           ###   ########.fr       */
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

t_coord	ft_initialize_complexe(t_fractal fractal, char **argv, int argc)
{
	t_coord	cmplx;

	if (fractal.fractal_type == 1)
		cmplx = ft_initialize_coord();
	else if (fractal.fractal_type == 2 && argc == 2)
	{
		cmplx.x = fractal.z_const.x;
		cmplx.y = fractal.z_const.y;
	}
	else if (fractal.fractal_type == 2 && argc < 5)
	{
		cmplx.x = ft_atof(argv[2]);
		cmplx.y = ft_atof(argv[3]);
	}
	else
		cmplx = ft_initialize_coord();
	return (cmplx);
}
