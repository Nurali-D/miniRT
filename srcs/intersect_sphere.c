/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:19:07 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 17:06:09 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		init_ret(t_closest *ret)
{
	ret->col = 0;
	vec_scalar(0, &ret->color);
	vec_scalar(0, &ret->norm);
	ret->t = INFINITY;
	vec_scalar(0, &ret->p_dot);
}

float		compute_root(t_dv *dot_o, t_dv *dot_d, t_sphere *sp)
{
	t_dv		oc;
	float		discriminant;
	t_dv		abc;
	t_dv		roots;

	roots.z = INFINITY;
	oc = vec_substract(dot_o, &sp->pos);
	abc.x = vec_dot_product(dot_d, dot_d);
	abc.y = 2 * vec_dot_product(&oc, dot_d);
	abc.z = vec_dot_product(&oc, &oc) - sp->diam * sp->diam / 4;
	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (roots.z);
	roots.x = (-1 * abc.y + sqrt(discriminant)) / (2 * abc.x);
	roots.y = (-1 * abc.y - sqrt(discriminant)) / (2 * abc.x);
	if (roots.x < roots.y)
		roots.z = roots.x;
	else
		roots.z = roots.y;
	if (roots.y < 0 && roots.x > 0)
		return (roots.x);
	return (roots.z);
}

int			check_light_cam(t_sphere *sp, t_dv *p, t_dv *vec_l)
{
	t_dv	l;
	t_dv	csp;
	t_dv	lsp;

	l = vec_sum(vec_l, p);
	csp = vec_substract(&g_scene->cam->pos, &sp->pos);
	lsp = vec_substract(&l, &sp->pos);
	if (vec_length(&csp) <= sp->diam * 0.5 && vec_length(&lsp) > sp->diam * 0.5)
		return (1);
	return (0);
}

t_closest	intersect_sp(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_sphere	*sp;
	t_closest	ret;
	int			c;

	init_ret(&ret);
	sp = data;
	if (lim.t2 == 1 && (c = check_light_cam(sp, dot_o, dot_d)))
	{
		ret.t = 0.5;
		return (ret);
	}
	ret.t = compute_root(dot_o, dot_d, sp);
	if (!(ret.t > lim.t1 && ret.t < lim.t2))
	{
		ret.t = INFINITY;
		return (ret);
	}
	ret.color = sp->color;
	ret.col = rgb_to_int(&ret.color);
	vec_p_dot(&ret.p_dot, dot_o, dot_d, ret.t);
	ret.norm = vec_substract(&ret.p_dot, &sp->pos);
	vec_normalize(&ret.norm);
	invert_normal(&ret.norm, ret.p_dot, dot_o);
	return (ret);
}
