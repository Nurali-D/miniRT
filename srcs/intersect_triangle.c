/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 02:43:33 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 19:22:51 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		find_t(t_trutils *s, t_triangle *tr, t_dv *dot_o, t_dv *dot_d)
{
	float	t;

	s->v1 = vec_substract(&tr->pnt2, &tr->pnt1);
	s->v2 = vec_substract(&tr->pnt3, &tr->pnt1);
	s->vec_p = vec_cross(*dot_d, s->v2);
	s->det = vec_dot_product(&s->v1, &s->vec_p);
	if (fabs(s->det) < 0.00001)
		return (INFINITY);
	s->c = 1 / s->det;
	s->vec_t = vec_substract(dot_o, &tr->pnt1);
	s->a = vec_dot_product(&s->vec_t, &s->vec_p) * s->c;
	if (s->a < 0 || s->a > 1)
		return (INFINITY);
	s->vec_t = vec_cross(s->vec_t, s->v1);
	s->b = vec_dot_product(dot_d, &s->vec_t) * s->c;
	if (s->b < 0 || s->a + s->b > 1)
		return (INFINITY);
	t = vec_dot_product(&s->v2, &s->vec_t) * s->c;
	return (t);
}

t_closest	intersect_tr(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_trutils	s;
	t_triangle	*tr;
	t_closest	ret;

	ret.col = 0;
	ret.t = INFINITY;
	tr = data;
	ret.t = find_t(&s, tr, dot_o, dot_d);
	if (!(ret.t > lim.t1 && ret.t < lim.t2) && (ret.t = INFINITY))
		return (ret);
	ret.color = tr->color;
	ret.col = rgb_to_int(&ret.color);
	ret.norm = vec_cross(s.v1, s.v2);
	vec_p_dot(&ret.p_dot, dot_o, dot_d, ret.t);
	invert_normal(&ret.norm, ret.p_dot, dot_o);
	return (ret);
}
