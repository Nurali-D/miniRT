/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:24:59 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 19:38:13 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_closest	intersect_pl_sq(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_dv		vec_x;
	t_square	*sq;
	t_closest	ret;
	t_dv		t;

	sq = data;
	ret.col = 0;
	ret.t = INFINITY;
	vec_x = vec_substract(dot_o, &sq->pos);
	t.x = vec_dot_product(&vec_x, &sq->ori);
	t.y = vec_dot_product(dot_d, &sq->ori);
	if (t.y == 0 || (t.x < 0 && t.y < 0) || (t.x > 0 && t.y > 0))
		return (ret);
	t.z = -1 * t.x / t.y;
	ret.t = t.z;
	if (!(ret.t >= lim.t1 && ret.t <= lim.t2) && (ret.t = INFINITY))
		return (ret);
	ret.color = sq->color;
	ret.col = rgb_to_int(&ret.color);
	ret.norm = sq->ori;
	vec_normalize(&ret.norm);
	vec_p_dot(&ret.p_dot, dot_o, dot_d, ret.t);
	invert_normal(&ret.norm, ret.p_dot, dot_o);
	return (ret);
}

int			p_in_square(t_dv a, t_dv c, t_dv p, float size)
{
	t_squtils	squ;
	t_dv		cross;

	squ.ca = vec_substract(&a, &c);
	squ.cp = vec_substract(&p, &c);
	squ.ap = vec_substract(&p, &a);
	squ.ac = vec_substract(&c, &a);
	if (!(vec_dot_product(&squ.ca, &squ.cp) >= 0
	&& vec_dot_product(&squ.ap, &squ.ac) >= 0))
		return (0);
	cross = vec_cross(squ.ca, squ.cp);
	squ.pn = vec_length(&cross) / vec_length(&squ.ca);
	if (squ.pn <= (0.5 * size))
		return (1);
	return (0);
}

void		get_ac(t_dv *a, t_dv *c, t_square *sq)
{
	if ((sq->ori.x == 0 && sq->ori.y == 0 && sq->ori.z == 1)
	&& sq->pos.x == 0 && sq->pos.y == 0)
	{
		a->x = sq->size * (-0.5);
		a->z = sq->pos.z;
		c->x = sq->size * 0.5;
		c->z = sq->pos.z;
	}
	if ((sq->ori.x == 1 && sq->ori.y == 0 && sq->ori.z == 0)
	&& sq->pos.x == 0 && sq->pos.y == 0)
	{
		a->y = sq->size * (-0.5);
		a->z = sq->pos.z;
		c->y = sq->size * 0.5;
		c->z = sq->pos.z;
	}
	if ((sq->ori.x == 0 && sq->ori.y == 1 && sq->ori.z == 0)
	&& sq->pos.x == 0 && sq->pos.y == 0)
	{
		a->x = sq->size * (-0.5);
		a->z = sq->pos.z;
		c->x = sq->size * 0.5;
		c->z = sq->pos.z;
	}
}

t_closest	intersect_sq(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim)
{
	t_dv		a;
	t_dv		c;
	t_square	*sq;
	t_closest	ret;

	sq = data;
	a = vec_cross(sq->pos, sq->ori);
	c = vec_cross(sq->ori, sq->pos);
	if (a.x == 0 && a.y == 0 && a.z == 0)
		get_ac(&a, &c, sq);
	vec_normalize(&a);
	vec_normalize(&c);
	vec_scalar(sq->size * 0.5, &a);
	vec_scalar(sq->size * 0.5, &c);
	a = vec_sum(&a, &sq->pos);
	c = vec_sum(&c, &sq->pos);
	ret = intersect_pl_sq(dot_o, dot_d, data, lim);
	if (ret.t != INFINITY && p_in_square(a, c, ret.p_dot, sq->size))
		return (ret);
	ret.t = INFINITY;
	return (ret);
}
