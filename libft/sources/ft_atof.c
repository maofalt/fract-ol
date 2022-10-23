/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:52:08 by motero            #+#    #+#             */
/*   Updated: 2022/10/23 05:29:50 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == ' ');
}

static int	ft_max_min(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	else
		return (INT_MIN);
}

double	ft_atof(const char *nptr)
{
	double a;
	char	**str;
	int c ;
	int	dec;

	a = 0.0;
	c = *nptr;
	while(c)
	{
		if (!ft_isdigit (c) || c != '.' || c != '-' || c != '+')
			return (0);
		c = *nptr++;
	}
	str = ft_split(nptr, '.');
	a += ft_atoi(str[0]);
	dec = ft_strlen(str[1]);
	a += ft_atoi(str[1]) * 10^-dec;
	return (a);
}
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int val;
	char strn1[] = "\t\n\r\v\f  469 \n";

	val = ft_atoi(strn1);
	printf("String value = %s\n", strn1);
	printf("Integer value = %d\n", val);

	char strn2[] = "\n\n\n    -46\b9 \n5d6";
	val = ft_atoi(strn2);
	printf("String value = %s\n", strn2);
	printf("Integer value = %d\n", val);

	return (0);
}*/
