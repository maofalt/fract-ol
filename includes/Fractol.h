/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/23 01:02:20 by motero           ###   ########.fr       */
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
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define BLUE_PIXEL 0xFF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x0

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
	t_coord		center_zoom;
	t_coord		px_coord;
	t_coord		polar_coord;
	t_coord		polar_der;
	t_coord		sq_coord;
	t_zoom		zoom;
	t_coord		offset;
	double		w;
	size_t		max_iter;
	t_xtrm		xtrm;
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

int			encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue);
void		img_pix_put(t_img *img, int x, int y, int color);
int			ft_valid_argument(int argc, char **argv);
size_t		ft_fractal_type(char **argv);

/*############################################################################*/
/*                  	MANAGE EVENTS FUNCTIONS                               */
/*############################################################################*/

int			ft_handle_keypress(int keysym, t_data *data);
int			ft_handle_boutonpress(int buttonsym, int x, int y, t_data *data);
int			ft_handle_keyrelease(int keysym, t_data *data);

/*############################################################################*/
/*                          RENDER FUNCTIONS                                  */
/*############################################################################*/

void		ft_render_background(t_img *img, int color);
int			ft_render_rect(t_img *img, t_rect rect);
int			ft_render_fractal(t_img *img, t_fractal *fractal);
int			ft_render(t_data *data);

/*############################################################################*/
/*                       COORDINATES FUNCTIONS                                */
/*############################################################################*/

t_coord		ft_initialize_coord(void);
t_zoom		ft_initialize_zoom(size_t fractal_type);
t_coord		ft_initialize_offset(size_t fractal_type);
t_xtrm		ft_initialize_extremes(size_t fractal_type);

/*############################################################################*/
/*                  CALCULATE MANDELBROT FUNCTIONS                            */
/*############################################################################*/

t_fractal	*ft_initialize_fractal(char **argv);
void		ft_calculate_mandelbrot(t_img *img, t_fractal *fractal, size_t px, size_t py);
void		ft_calculate_julia(t_img *img, t_fractal *fractal, size_t px, size_t py);

#endif
