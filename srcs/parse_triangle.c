/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:39:56 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 17:35:05 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_tr_par(char *line, t_triangle *tr)
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
			line = get_position(line, &tr->pnt1);
		else if (i == 1 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_position(line, &tr->pnt2);
		else if (i == 2 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_position(line, &tr->pnt3);
		else if (i == 3 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &tr->color);
		else
			print_error_exit("Invalid tr input parameters", PARSE_ERROR);
	}
	return (line);
}

void	parse_triangle(char *line)
{
	t_triangle	*tr_new;
	t_object	*tmp;
	t_object	*tr;

	if (!(tr_new = (t_triangle*)malloc(sizeof(t_triangle))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	if (!(tr = (t_object*)malloc(sizeof(t_object))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	line = get_tr_par(line, tr_new);
	tr->data = tr_new;
	tr->intersect_funct = &intersect_tr;
	tr->next = NULL;
	if (!g_scene->obj)
		g_scene->obj = tr;
	else
	{
		tmp = g_scene->obj;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = tr;
	}
}
