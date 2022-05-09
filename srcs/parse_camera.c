/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:26:40 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/02 15:30:43 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char		*get_cam_par(char *line, t_camera *cam)
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
			line = get_position(line, &cam->pos);
		else if (i == 1 && ((*line >= '0' && *line <= '9')
		|| *line == '-' || *line == '+') && (i++))
			line = get_ori(line, &cam->ori);
		else if (i == 2 && (*line >= '0' && *line <= '9') && (i++))
		{
			cam->fov = ft_atoi(line);
			line += ft_intlen(cam->fov, 10);
			if (!(cam->fov >= 0 && cam->fov <= 180))
				print_error_exit("Invalid FOV input", PARSE_ERROR);
		}
		else
			print_error_exit("Invalid c input parameters", PARSE_ERROR);
	}
	return (line);
}

t_camera	*parse_camera(char *line, t_camera *cam)
{
	t_camera	*cam_new;
	t_camera	*tmp;

	if (!(cam_new = (t_camera*)malloc(sizeof(t_camera))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	cam_new->next = NULL;
	cam_new->prev = NULL;
	if (cam)
	{
		tmp = cam;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cam_new;
		cam_new->prev = tmp;
	}
	line = get_cam_par(line, cam_new);
	if (!(cam))
		cam = cam_new;
	return (cam);
}
