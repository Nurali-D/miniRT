/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:38:24 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/02 04:15:25 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_cy_diam(char *line, t_cylinder *cy)
{
	cy->diam = ft_atof(line);
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	return (line);
}

char	*get_cy_height(char *line, t_cylinder *cy)
{
	cy->height = ft_atof(line);
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	cy->pb = vec_scalar_ret(cy->height, &cy->ori);
	cy->pb = vec_sum(&cy->pos, &cy->pb);
	cy->c = -1;
	return (line);
}

char	*get_cy_par(char *line, t_cylinder *cy)
{
	int	i;

	i = 0;
	line += 2;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (i == 0 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (++i))
			line = get_position(line, &cy->pos);
		else if (i == 1 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_ori(line, &cy->ori);
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
			line = get_cy_diam(line, cy);
		else if (i == 3 && (*line >= '0' && *line <= '9') && (i++))
			line = get_cy_height(line, cy);
		else if (i == 4 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &cy->color);
		else
			print_error_exit("Invalid cy input parameters", PARSE_ERROR);
	}
	return (line);
}

void	parse_cylinder(char *line)
{
	t_cylinder	*cy_new;
	t_object	*tmp;
	t_object	*cy;

	if (!(cy_new = (t_cylinder*)malloc(sizeof(t_cylinder))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	if (!(cy = (t_object*)malloc(sizeof(t_object))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	line = get_cy_par(line, cy_new);
	cy->data = cy_new;
	cy->intersect_funct = &intersect_cy;
	cy->next = NULL;
	if (!g_scene->obj)
		g_scene->obj = cy;
	else
	{
		tmp = g_scene->obj;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = cy;
	}
}
