/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 22:27:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0xFF00
# define BLUE_PIXEL 0xFF
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x0
# define C1 0x11b899
# define C2 0x9dbf9e
# define C3 0x57bc9c
# define C4 0xb7cbaa
# define C5 0xd0d6b5
# define C6 0xe5c6b1
# define C7 0xee7674
# define C8 0xf49690
# define C9 0xf9b5ac

# include <stdint.h>

/*############################################################################*/
/*                          COLOR FUNCTIONS                                  */
/*############################################################################*/

/*Encode of 4 unint8_t into a utin32_t, so mlx is able to read RGB in Hex */
uint32_t	encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue);

#endif