/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:41:56 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 15:32:45 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		exit_program(void)
{
	free_scene();
	exit(0);
	return (0);
}

void	change_o(int k, t_dv *o)
{
	if (k == KEYCODE_A)
		o->x += -0.5;
	else if (k == KEYCODE_D)
		o->x += 0.5;
	else if (k == KEYCODE_S)
		o->y += -0.5;
	else if (k == KEYCODE_W)
		o->y += 0.5;
	else if (k == KEYCODE_F)
		o->z += -0.5;
	else if (k == KEYCODE_R)
		o->z += 0.5;
}

void	change_r(int k, t_dv *r)
{
	if (k == KEYCODE_DOWN)
		r->x += -0.1;
	else if (k == KEYCODE_UP)
		r->x += 0.1;
	else if (k == KEYCODE_LEFT)
		r->y += -0.1;
	else if (k == KEYCODE_RIGHT)
		r->y += 0.1;
	else if (k == KEYCODE_1)
		r->z += -0.1;
	else if (k == KEYCODE_2)
		r->z += 0.1;
}

void	change_or(int k)
{
	t_dv	*o;
	t_dv	*r;

	o = &g_scene->cam->pos;
	r = &g_scene->cam->ori;
	change_o(k, o);
	change_r(k, r);
}

int		handle_key(int k, t_window *w)
{
	if (k == 53)
		return (exit_program());
	if (!(k >= 0 && k <= 3) && !(k >= 12 && k <= 15) &&
		!(k >= 123 && k <= 126) && k != 83 && k != 84)
		return (0);
	change_or(k);
	if (k == KEYCODE_Q)
	{
		if (!(g_scene->cam->prev))
			return (0);
		g_scene->cam = g_scene->cam->prev;
	}
	if (k == KEYCODE_E)
	{
		if (!(g_scene->cam->next))
			return (0);
		g_scene->cam = g_scene->cam->next;
	}
	if (w->img.img)
		mlx_destroy_image(w->pt->mlx_ptr, w->img.img);
	ray_tracing(w->pt->mlx_ptr, &w->img);
	mlx_clear_window(w->pt->mlx_ptr, w->pt->win_ptr);
	mlx_put_image_to_window(w->pt->mlx_ptr, w->pt->win_ptr, w->img.img, 0, 0);
	return (0);
}
