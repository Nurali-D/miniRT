/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:24:00 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/23 16:10:53 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_resolution(char *line, t_resolution *res)
{
	int	i;

	i = 0;
	line++;
	while (*line)
		if (*line == ' ' || *line == '\t')
			line++;
		else if (i < 2 && *line >= '0' && *line <= '9')
		{
			if (i == 0 && (++i))
			{
				res->x = ft_atoi(line);
				line += ft_intlen(res->x, 10);
			}
			else if (i == 1 && (++i))
			{
				res->y = ft_atoi((const char*)line);
				line += ft_intlen(res->y, 10);
			}
		}
		else
			print_error_exit("Invalid R input parameters", PARSE_ERROR);
	if (res->x == 0 || res->y == 0)
		print_error_exit("Invalid R input parameters", PARSE_ERROR);
}
