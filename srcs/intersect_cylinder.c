/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:26:45 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 20:33:23 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			check_light_camera(t_cylinder *cy, t_dv *p, t_dv *vec_l)
{
	t_dv	l;
	t_dv	al;
	t_dv	ac;
	t_dv	dot;
	float	proj;

	l = vec_sum(vec_l, p);
	ac = vec_substract(&g_scene->cam->pos, &cy->pos);
	proj = vec_dot_product(&cy->ori, &ac);
	if (proj < 0 || proj > cy->height)
		return (2);
	vec_p_dot(&dot, &cy->pos, &cy->ori, proj);
	if ((len_ab(&dot, &g_scene->cam->pos)) > cy->diam * 0.5)
		return (2);
	al = vec_substract(&l, &cy->pos);
	proj = vec_dot_product(&cy->ori, &al);
	if (proj < 0 || proj > cy->height)
		return (0);
	vec_p_dot(&dot, &cy->pos, &cy->ori, proj);
	if ((len_ab(&dot, &l)) < cy->diam * 0.5)
		return (1);
	return (0);
}

void		fill_return(t_closest *ret, t_cylinder *cy,
						t_dv *dot_o, t_dv *vec_d)
{
	ret->color = cy->color;
	ret->col = rgb_to_int(&ret->color);
	vec_p_dot(&ret->p_dot, dot_o, vec_d, ret->t);
	invert_normal(&ret->norm, ret->p_dot, dot_o);
}

t_closest	get_t_for_light(t_cylinder *cy, t_dv *dot_o,
							t_dv *dot_d, t_dv *vec_d)
{
	float		len_dir;
	t_closest	ret;

	len_dir = vec_length(dot_d);
	ret = cyl_intersect(dot_o, vec_d, cy, ret);
	ret.t = ret.t / len_dir;
	return (ret);
}

t_closest	intersect_cy(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_cylinder		*cy;
	t_closest		ret;
	t_dv			vec_d;

	vec_d = *dot_d;
	vec_normalize(&vec_d);
	cy = data;
	init_ret(&ret);
	if (lim.t2 == 1 && (cy->c = check_light_camera(cy, dot_o, dot_d)))
		ret = get_t_for_light(cy, dot_o, dot_d, &vec_d);
	else if (lim.t2 == 1 && cy->c == 0)
	{
		ret.t = 0.5;
		return (ret);
	}
	else if (lim.t2 == INFINITY)
		ret = cyl_intersect(dot_o, &vec_d, cy, ret);
	if (!(ret.t > lim.t1 && ret.t < lim.t2))
	{
		ret.t = INFINITY;
		return (ret);
	}
	if (lim.t2 == INFINITY)
		fill_return(&ret, cy, dot_o, &vec_d);
	return (ret);
}
