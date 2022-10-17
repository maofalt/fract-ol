/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/17 23:10:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define BLUE_PIXEL 0xFF
# define WHITE_PIXEL 0xFFFFFF

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
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

/* The x and y coordinates of the rect corresponds to its upper left corner. */
typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}	t_rect;

typedef struct s_mdbt
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
	size_t	max_iter;
}	t_mdbt;

/*############################################################################*/
/*                          MAIN FUNCTIONS                                    */
/*############################################################################*/

int		encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue);
void	img_pix_put(t_img *img, int x, int y, int color);

/*############################################################################*/
/*                  	MANAGE EVENTS FUNCTIONS                               */
/*############################################################################*/

int		ft_handle_keypress(int keysym, t_data *data);
int		ft_handle_keyrelease(int keysym, t_data *data);

/*############################################################################*/
/*                          RENDER FUNCTIONS                                  */
/*############################################################################*/

void	ft_render_background(t_img *img, int color);
int		ft_render_rect(t_img *img, t_rect rect);
int		ft_render(t_data *data);

/*############################################################################*/
/*                  CALCULATE MANDELBROT FUNCTIONS                            */
/*############################################################################*/

int		ft_cal_mandelbrot(t_img *img, t_mdbt mdbt);

#endif
