/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 21:41:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

/* bpp = bits per pixel */
typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_distance
{
	size_t	min;
	size_t	max;
}	t_distance;

/* The x and y coordinates of the rect corresponds to its upper left corner. */
typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
}	t_rect;

/*structure for ease of us of coordonates on aa x-y axis*/
typedef struct s_coord
{
	double		x;
	double		y;
}	t_coord;

typedef struct s_zoom
{
	double		kx;
	double		ky;
}	t_zoom;

typedef struct s_xtrm
{
	double		re_max;
	double		re_min;
	double		im_max;
	double		im_min;
}	t_xtrm;

/*Structure for Mandelbrot fractal**
** 1- Scaled coordinates of pixel */
typedef struct s_fractal
{
	size_t		fractal_type;
	t_coord		px_coord;
	t_coord		polar_coord;
	t_coord		polar_der;
	t_coord		sq_coord;
	t_coord		dc;
	t_coord		old;
	t_zoom		zoom;
	t_coord		offset;
	double		w;
	size_t		max_iter;
	t_xtrm		xtrm;
	t_coord		z_const;
	size_t		update;
	size_t		color_method;
	uint32_t	*palette;
	double		angle;
	double		h;
	double		r;
}	t_fractal;

/* Struucture transporting  pointer from mlx */
typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			x;
	int			y;
	size_t		ticks;
	t_img		img;
	t_fractal	*fractal;
}	t_data;

#endif