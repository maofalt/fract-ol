/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:06:37 by motero            #+#    #+#             */
/*   Updated: 2022/10/28 22:28:19 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Colors.h>

/* Encode of 4 unint8_t into a utin32_t, so mlx is able to read RGB in Hex,**
** thourgh bit shifting. */
uint32_t	encode_rgb(uint8_t hue, uint8_t red, uint8_t green, uint8_t blue)
{
	return (hue << 24 | red << 16 | green << 8 | blue);
}
