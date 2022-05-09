/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:37:16 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/16 21:25:59 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_sq_par(char *line, t_square *sq)
{
	int	i;

	i = 0;
	line += 2;
	while (*line)
		if (*line == ' ' || *line == '\t')
			line++;
		else if (i == 0 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (++i))
			line = get_position(line, &sq->pos);
		else if (i == 1 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_ori(line, &sq->ori);
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
		{
			sq->size = ft_atof(line);
			while ((*line >= '0' && *line <= '9') || *line == '.')
				line++;
		}
		else if (i == 3 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &sq->color);
		else
			print_error_exit("Invalid sq input parameters", PARSE_ERROR);
	return (line);
}

void	parse_square(char *line)
{
	t_square	*sq_new;
	t_object	*tmp;
	t_object	*sq;

	if (!(sq_new = (t_square*)malloc(sizeof(t_square))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	if (!(sq = (t_object*)malloc(sizeof(t_object))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	line = get_sq_par(line, sq_new);
	sq->data = sq_new;
	sq->intersect_funct = &intersect_sq;
	sq->next = NULL;
	if (!g_scene->obj)
		g_scene->obj = sq;
	else
	{
		tmp = g_scene->obj;
		while (tmp)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		tmp->next = sq;
	}
}
