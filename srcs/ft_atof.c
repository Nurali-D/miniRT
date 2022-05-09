/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:35:36 by ltulune           #+#    #+#             */
/*   Updated: 2021/02/20 21:10:09 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_exp(char *str)
{
	float	n;
	int		i;

	i = 0;
	str++;
	if ((*str >= '0' && *str <= '9')
	|| *str == '-' || *str == '+')
	{
		i = ft_atoi((const char*)str);
		n = ft_pow_n(10, i);
	}
	else
		n = 1;
	return (n);
}

static float	get_fractional_part(char *str)
{
	float	n;
	int		i;

	i = 0;
	n = 0;
	str++;
	while ((*str) && *str >= '0' && *str <= '9')
	{
		i++;
		n += (*str - '0') / ft_pow_n(10, i);
		str++;
	}
	return (n);
}

static float	ft_atof2(char *str, float n, int buf)
{
	while (*str)
		if (*str >= '0' && *str <= '9')
		{
			buf = ft_atoi((const char*)str);
			n = buf;
			str += ft_intlen(buf, 10);
		}
		else if (*str == '.')
		{
			n += get_fractional_part(str);
			str++;
			while (*str >= '0' && *str <= '9')
				str++;
			if (*str == 'e' || *str == 'E')
			{
				n *= get_exp(str++);
				while ((*str >= '0' && *str <= '9')
				|| *str == '-' || *str == '+')
					str++;
				break ;
			}
		}
		else
			break ;
	return (n);
}

float			ft_atof(char *str)
{
	float	n;
	int		buf;
	int		sign;

	sign = 0;
	n = 0;
	while (*str)
	{
		if (!(buf = 0) && (*str == ' ' || *str == '\t'))
			str++;
		else if ((*str == '-' || *str == '+') && (str++))
		{
			if (!(*str >= '0' && *str <= '9'))
				break ;
			sign = (*(str - 1) == '-') ? 1 : 2;
		}
		if ((*str >= '0' && *str <= '9') || *str == '.')
		{
			n = ft_atof2(str, n, buf);
			break ;
		}
	}
	if (sign == 1)
		n *= -1;
	return (n);
}
