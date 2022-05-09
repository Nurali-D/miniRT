/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 02:29:33 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 15:47:48 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_cameras(void)
{
	t_camera	*tmp;
	t_camera	*cams;

	cams = g_scene->cam;
	tmp = cams;
	while (cams)
	{
		tmp = cams;
		cams = cams->next;
		free(tmp);
	}
}

void	free_lights(void)
{
	t_light	*tmp;
	t_light	*light;

	light = g_scene->lgt;
	tmp = light;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
}

void	free_objects(void)
{
	t_object	*tmp;
	t_object	*object;

	object = g_scene->obj;
	tmp = object;
	while (object)
	{
		tmp = object;
		object = object->next;
		free(tmp->data);
		free(tmp);
	}
}

void	free_scene(void)
{
	t_window	*w;

	w = g_scene->w;
	free_cameras();
	free_lights();
	free_objects();
	if (w->img.img)
		mlx_destroy_image(w->pt->mlx_ptr, w->img.img);
	if ((w->pt->win_ptr))
		mlx_destroy_window(w->pt->mlx_ptr, w->pt->win_ptr);
	free(g_scene);
}

void	print_error_exit(char *str, int err)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" (exit code: ", STDERR_FILENO);
	ft_putnbr_fd(err, STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
	if (g_scene)
		free_scene();
	exit(err);
}
