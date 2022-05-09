/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:34:10 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/05 00:07:48 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_pl_par(char *line, t_plane *pl)
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
			line = get_position(line, &pl->pos);
		else if (i == 1 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_ori(line, &pl->ori);
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &pl->color);
		else
			print_error_exit("Invalid pl input parameters", PARSE_ERROR);
	}
	return (line);
}

void	parse_plane(char *line)
{
	t_plane		*pl_new;
	t_object	*tmp;
	t_object	*pl;

	if (!(pl_new = (t_plane*)malloc(sizeof(t_plane))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	if (!(pl = (t_object*)malloc(sizeof(t_object))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	line = get_pl_par(line, pl_new);
	pl->data = pl_new;
	pl->intersect_funct = &intersect_pl;
	pl->next = NULL;
	if (!g_scene->obj)
		g_scene->obj = pl;
	else
	{
		tmp = g_scene->obj;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = pl;
	}
}
