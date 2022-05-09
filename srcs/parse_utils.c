/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:03:23 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/22 21:05:29 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			get_xyz(char *line, float *n, int flag)
{
	float	buf;
	int		i;

	i = 0;
	buf = ft_atof(line);
	if (flag == 1 && !(buf >= 0 && buf <= 255))
		print_error_exit("Color value is not in range [0; 255]", PARSE_ERROR);
	if (flag == 3 && !(buf >= -1 && buf <= 1))
		print_error_exit("Invalid orient. vector value [-1; 1]", PARSE_ERROR);
	*n = buf;
	while ((*line >= '0' && *line <= '9') || *line == '.'
	|| *line == '-' || *line == '+')
	{
		i++;
		line++;
	}
	return (i);
}

char		*get_color(char *line, t_dv *color)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || (*line == ',' && (++comma)))
			line++;
		else if (i == 0 && *line >= '0' && *line <= '9' && (++i))
			line += get_xyz(line, &color->x, 1);
		else if (i == 1 && (i++))
			line += get_xyz(line, &color->y, 1);
		else if (i == 2 && (i++))
			line += get_xyz(line, &color->z, 1);
		else
			print_error_exit("Invalid color input", PARSE_ERROR);
		if (i > 2)
			break ;
	}
	return (line);
}

char		*get_position(char *line, t_dv *pos)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || (*line == ',' && (++comma)))
			line++;
		else if (i == 0 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (++i))
			line += get_xyz(line, &pos->x, 2);
		else if (i == 1 && (i++))
			line += get_xyz(line, &pos->y, 2);
		else if (i == 2 && (i++))
			line += get_xyz(line, &pos->z, 2);
		else
			print_error_exit("Invalid position input", PARSE_ERROR);
		if (i > 2)
			break ;
	}
	return (line);
}

char		*get_ori(char *line, t_dv *ori)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || (*line == ',' && (++comma)))
			line++;
		else if (i == 0 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (++i))
			line += get_xyz(line, &ori->x, 3);
		else if (i == 1 && (i++))
			line += get_xyz(line, &ori->y, 3);
		else if (i == 2 && (i++))
			line += get_xyz(line, &ori->z, 3);
		else
			print_error_exit("Invalid orientation input", PARSE_ERROR);
		if (i > 2)
			break ;
	}
	return (line);
}
