/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:35:51 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/03 17:28:14 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_sp_par(char *line, t_sphere *sp)
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
			line = get_position(line, &sp->pos);
		else if (i == 1 && (*line >= '0' && *line <= '9') && (i++))
		{
			sp->diam = ft_atof(line);
			while ((*line >= '0' && *line <= '9') || *line == '.')
				line++;
		}
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &sp->color);
		else
			print_error_exit("Invalid sp input parameters", PARSE_ERROR);
	}
	return (line);
}

void	parse_sphere(char *line)
{
	t_sphere	*sp_new;
	t_object	*tmp;
	t_object	*sp;

	if (!(sp_new = (t_sphere*)malloc(sizeof(t_sphere))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	if (!(sp = (t_object*)malloc(sizeof(t_object))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	line = get_sp_par(line, sp_new);
	sp->data = sp_new;
	sp->intersect_funct = &intersect_sp;
	sp->next = NULL;
	if (!g_scene->obj)
		g_scene->obj = sp;
	else
	{
		tmp = g_scene->obj;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = sp;
	}
}
