/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:55:48 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 15:42:05 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_g_scene(void)
{
	g_scene->res.x = 0;
	g_scene->res.y = 0;
	g_scene->al.ratio = 0;
	g_scene->al.color.x = 0;
	g_scene->al.color.y = 0;
	g_scene->al.color.z = 0;
	g_scene->cam = NULL;
	g_scene->lgt = NULL;
	g_scene->obj = NULL;
}

void	parse_elements2(char *line)
{
	if (*line == 'p' && *(line + 1) == 'l')
		parse_plane(line);
	else if (*line == 's' && *(line + 1) == 'p')
		parse_sphere(line);
	else if (*line == 's' && *(line + 1) == 'q')
		parse_square(line);
	else if (*line == 'c' && *(line + 1) == 'y')
		parse_cylinder(line);
	else if (*line == 't' && *(line + 1) == 'r')
		parse_triangle(line);
	else if (*line == '\0')
		return ;
	else
		print_error_exit("Invalid type identifier", PARSE_ERROR);
	return ;
}

void	parse_elements(char *line)
{
	static int	r;
	static int	a;

	if (r > 1 || a > 1)
		print_error_exit("File .rt must contain one R and one A", PARSE_ERROR);
	else if (*line == 'R' && (++r))
		parse_resolution(line, &g_scene->res);
	else if (*line == 'A' && (++a))
		parse_amb_light(line, &g_scene->al);
	else if (*line == 'c' && *(line + 1) != 'y')
		g_scene->cam = parse_camera(line, g_scene->cam);
	else if (*line == 'l')
		g_scene->lgt = parse_light(line, g_scene->lgt);
	else
		parse_elements2(line);
}

void	parse_scene(int argc, char **argv, t_window *w)
{
	int		fd;
	char	*line;

	if (!(g_scene = (t_scene*)malloc(sizeof(t_scene))))
		print_error_exit("MALLOC ERROR", MALLOC_ERROR);
	init_g_scene();
	g_scene->w = w;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		print_error_exit("invalid input", INPUT_ERROR);
	while (get_next_line(fd, &line))
	{
		parse_elements(line);
		free(line);
	}
	parse_elements(line);
	free(line);
	close(fd);
}
