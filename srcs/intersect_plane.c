/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:02:47 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 19:22:37 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		invert_normal(t_dv *norm, t_dv p, t_dv *o)
{
	t_dv	po;
	float	d;

	po = vec_substract(o, &p);
	vec_normalize(&po);
	d = vec_dot_product(&po, norm);
	if (d < 0)
		vec_scalar(-1, norm);
}

t_closest	intersect_pl(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_dv		vec_x;
	t_plane		*pl;
	t_closest	ret;
	t_dv		t;

	pl = data;
	ret.col = 0;
	ret.t = INFINITY;
	vec_x = vec_substract(dot_o, &pl->pos);
	t.x = vec_dot_product(&vec_x, &pl->ori);
	t.y = vec_dot_product(dot_d, &pl->ori);
	if (t.y == 0 || (t.x < 0 && t.y < 0) || (t.x > 0 && t.y > 0))
		return (ret);
	t.z = -1 * t.x / t.y;
	ret.t = t.z;
	if (!(ret.t > lim.t1 && ret.t < lim.t2) && (ret.t = INFINITY))
		return (ret);
	ret.color = pl->color;
	ret.col = rgb_to_int(&ret.color);
	ret.norm = pl->ori;
	vec_normalize(&ret.norm);
	vec_p_dot(&ret.p_dot, dot_o, dot_d, ret.t);
	invert_normal(&ret.norm, ret.p_dot, dot_o);
	return (ret);
}
