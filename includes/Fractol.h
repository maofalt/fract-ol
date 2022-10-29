/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/29 22:23:03 by motero           ###   ########.fr       */
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
# include "Structures.h"

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
/*                          RENDER FUNCTIONS                                  */
/*############################################################################*/

	/* We render fracta if update == 1, in this case if a hook or **
	**event has modified underlying constants*/
int			ft_render(t_data *data);
	/*Deprecated functions, for test and debug functions intended **
	**to fill mlx_img with one color*/
void		ft_render_background(t_img *img, int color);
	/*For mandelbrot (except 2) we optimize to calculae only haf of it*/
void		ft_calculation_limits(t_fractal *fractal, t_distance *y);
	/* pan into each px & apply and apply sequence formula 'til escape radius*/
void		ft_calculate_pixels(t_data *data, t_distance *y);
int			ft_render_fractal(t_data *data);

/*############################################################################*/
/*                         OPTIMIZATION FUNCTIONS                             */
/*############################################################################*/
	/* function for mandelbrot allowing us to memcpy the "big size" **
	**and saving time. We apply the same formulae as mxl_put pixel on img */
void		ft_optimization_symmetry(t_data *data, t_distance *y);

int			ft_check_shapes(t_img *img, t_fractal *fractal, size_t px, size_t py);

int			ft_check_period(t_fractal *fractal, double *period, size_t *i);

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
/*                  CALCULATE FRACTAL FUNCTIONS                               */
/*############################################################################*/
/*Inintialzie all fractal structure and cnts, depending on the fractal type*/
t_fractal	*ft_initialize_fractal(char **argv, int argc);
void		ft_cal_mandel(t_img *img, t_fractal *fractal, size_t px, size_t py);
size_t		ft_mandel_loop(t_fractal *fractal);
void		ft_calculate_julia(t_img *img, t_fractal *fractal, size_t px, size_t py);
void		ft_calculate_burning_ship(t_img *img, t_fractal *fractal, size_t px, size_t py);

/*############################################################################*/
/*                      CALCULATE MATH COMPLEXE                               */
/*############################################################################*/

void		ft_derivate_complex(t_fractal *fractal);

#endif
