/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:25:10 by ltulune           #+#    #+#             */
/*   Updated: 2021/02/17 09:10:00 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_amb_light(char *line, t_alight *al)
{
	int	i;

	i = 0;
	line++;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (i == 0 && *line >= '0' && *line <= '1')
		{
			al->ratio = ft_atof(line);
			i++;
			while ((*line >= '0' && *line <= '9') || *line == '.')
				line++;
		}
		else if (i > 0 && *line >= '0' && *line <= '9')
			line = get_color(line, &al->color);
		else
			print_error_exit("Invalid A input parameters", PARSE_ERROR);
	}
}
