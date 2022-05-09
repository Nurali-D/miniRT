/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:25:43 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 17:04:36 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_closest	closest_intersection(t_dv *dot_o, t_dv *vec_d, float min, float max)
{
	t_closest	closest;
	t_object	*tmp;
	t_closest	t_cl;
	t_root		lim;

	lim.t1 = min;
	lim.t2 = max;
	tmp = g_scene->obj;
	init_ret(&closest);
	while (tmp)
	{
		t_cl = tmp->intersect_funct(dot_o, vec_d, tmp->data, lim);
		if (t_cl.t < closest.t)
			closest = t_cl;
		tmp = tmp->next;
	}
	return (closest);
}

void		compute_color_intensity(t_closest *cl, t_dv *vec_d)
{
	float		i;
	t_light		*tmp;
	t_dv		l_vec;
	t_dv		color;
	t_dv		light_color;

	color = vec_scalar_ret(g_scene->al.ratio, &g_scene->al.color);
	color = mix_col(&cl->color, &color);
	tmp = g_scene->lgt;
	while (tmp)
	{
		i = 0;
		l_vec = vec_substract(&tmp->pos, &cl->p_dot);
		i = compute_i(*cl, vec_d, &l_vec, tmp);
		if (i)
		{
			light_color = vec_scalar_ret(i, &tmp->color);
			light_color = mix_col(&cl->color, &light_color);
			color = vec_sum(&color, &light_color);
		}
		tmp = tmp->next;
	}
	cl->color = color;
}

int			get_pixel_color(t_dv *dot_o, t_dv *dot_d)
{
	t_closest	closest;

	closest = closest_intersection(dot_o, dot_d, 1, INFINITY);
	if (closest.t != INFINITY)
	{
		compute_color_intensity(&closest, dot_d);
		closest.col = rgb_to_int(&closest.color);
	}
	return (closest.col);
}
