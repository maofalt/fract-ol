/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 02:04:06 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define RE_MAX 0.47
# define RE_MIN -2.0
# define IM_MAX 1.12
# define IM_MIN -1.12
# define MLX_ERROR 1
# define PI 3.14159265359

# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdlib.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "Events.h"
# include "Colors.h"
# include <complex.h>

/*############################################################################*/
/*                      STRUCTURES DEFINITION                                 */
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

/*############################################################################*/
/*                          MAIN FUNCTIONS                                    */
/*############################################################################*/

	/* Validate for Julia fractals that the complexe form argumnts are valid*/
int			ft_valid_d(char *str);
	/* Function parsing which type of fractal we are going to work with*/
int			ft_valid_argument(int argc, char **argv);
	/*After validating, that args are OK, we parse  the fractal_type (ft) */
size_t		ft_fractal_type(int argc, char **argv);
	/*Set of instructions to use ./fractal program*/
void		ft_error_message(void);
	/*destroy window ptr, mlx img ptr , free palette str, fractal structure**
	** and destoy display*/
void		ft_free_all(t_data *data);

/*############################################################################*/
/*                          MLX UTILS FUNCTIONS                               */
/*############################################################################*/

	/*Put a pixel of a given color, passing a polar coordiate **
	** into img pointer of  MLX*/
void		img_pix_put(t_img *img, int x, int y, int color);
	/*Hooks (boutton press, button reease, destoy window, **
	**key release and mxloop here)*/
void		ft_mlx_engine(t_data *data);
	/*engine start and alloc mlxpt, win ptr  and img*/
int			ft_mlx_start(t_data *data);

/*############################################################################*/
/*                  	MANAGE EVENTS FUNCTIONS                               */
/*############################################################################*/

int			ft_handle_keypress(int keysym, t_data *data);
int			ft_handle_boutonpress(int buttonsym, int x, int y, t_data *data);
int			ft_handle_keyrelease(int keysym, t_data *data);
int			ft_destroy_window(t_data *data);

/*############################################################################*/
/*                          RENDER FUNCTIONS                                  */
/*############################################################################*/

	/* We render fracta if update == 1, in this case if a hook or **
	**event has modified underlying constants*/
int			ft_render(t_data *data);
	/*Deprecated functions, for test and debug functions intended **
	**to fill mlx_img with one color*/
void		ft_render_background(t_img *img, int color);
	/*We calclate the exact offst for each  fractal type in order to center it*/
void		ft_recenter_fractal(t_fractal *fractal, t_distance *y);
int			ft_render_fractal(t_img *img, t_fractal *fractal);

/*############################################################################*/
/*                   INITIALIZE STRUCTURE FUNCTIONS                           */
/*############################################################################*/

t_coord		ft_initialize_coord(void);
t_zoom		ft_initialize_zoom(size_t fractal_type);
t_coord		ft_initialize_offset(size_t fractal_type);
t_xtrm		ft_initialize_extremes(size_t fractal_type);
t_coord		ft_initialize_complexe(t_fractal fractal, char **argv, int argc);
size_t		ft_initialize_fractal_type(int argc, char **argv);

/*############################################################################*/
/*                  CALCULATE MANDELBROT FUNCTIONS                            */
/*############################################################################*/

t_fractal	*ft_initialize_fractal(char **argv, int argc);
int			ft_check_shapes(t_img *img, t_fractal *fractal, size_t px, size_t py);
uint32_t	ft_color_fractal(t_fractal *fractal, double i);
void		ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py);
void		ft_calculate_julia(t_img *img, t_fractal *fractal, size_t px, size_t py);
void		ft_calculate_burning_ship(t_img *img, t_fractal *fractal, size_t px, size_t py);
uint32_t	ft_bernstein_interpolation(double i);
uint32_t	ft_linear_interpolation(uint32_t color1, uint32_t color2, double temp);

#endif
