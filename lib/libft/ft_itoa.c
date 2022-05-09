/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 09:35:55 by ltulune           #+#    #+#             */
/*   Updated: 2021/02/16 22:49:49 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen10(int num)
{
	int			i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static char		*ft_wrnum(char *b, long int c)
{
	int			i;

	if (c < 0 && (i = ft_intlen10(c)) > 0)
	{
		b[0] = '-';
		c *= -1;
		b[i + 1] = '\0';
		while (c)
		{
			b[i] = c % 10 + '0';
			c /= 10;
			i--;
		}
	}
	else if ((i = ft_intlen10(c)) > 0)
	{
		b[i] = '\0';
		while (c)
		{
			b[i - 1] = c % 10 + '0';
			c /= 10;
			i--;
		}
	}
	return (b);
}

char			*ft_itoa(int n)
{
	char		*ret;
	long int	nl;

	if (!(ret = (char*)malloc((ft_intlen10(n) + 2) * sizeof(char))))
		return (NULL);
	nl = n;
	if (n == 0)
	{
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	return (ft_wrnum(ret, nl));
}
