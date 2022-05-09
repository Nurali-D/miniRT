/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:27:50 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/02 15:38:08 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_lgt_par(char *line, t_light *lgt)
{
	int	i;

	i = 0;
	line++;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else if (i == 0 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (++i))
			line = get_position(line, &lgt->pos);
		else if (i == 1 && (*line >= '0' && *line <= '1') && (i++))
		{
			lgt->ratio = ft_atof(line);
			if (!(lgt->ratio >= 0 && lgt->ratio <= 1))
				print_error_exit("Invalid lgt brihtness[0; 1]", PARSE_ERROR);
			while ((*line >= '0' && *line <= '9') || *line == '.')
				line++;
		}
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
			line = get_color(line, &lgt->color);
		else
			print_error_exit("Invalid l input parameters", PARSE_ERROR);
	}
	return (line);
}

t_light	*parse_light(char *line, t_light *lgt)
{
	t_light	*lgt_new;
	t_light	*tmp;

	if (!(lgt_new = (t_light*)malloc(sizeof(t_light))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	lgt_new->next = NULL;
	if (lgt)
	{
		tmp = lgt;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lgt_new;
	}
	line = get_lgt_par(line, lgt_new);
	if (!(lgt))
		lgt = lgt_new;
	return (lgt);
}
