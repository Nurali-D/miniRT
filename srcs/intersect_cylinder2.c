/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:31:45 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 18:03:34 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dv		get_norm(t_utcylinder u, t_dv *rd, float ra, int flag)
{
	t_dv	a;
	t_dv	b;
	t_dv	c;
	t_dv	norm;

	if (flag == 1)
	{
		a = vec_scalar_ret(u.t, rd);
		a = vec_sum(&u.oc, &a);
		b = vec_scalar_ret(u.y / u.caca, &u.ca);
		c = vec_substract(&a, &b);
		norm = vec_scalar_ret(1 / ra, &c);
	}
	if (flag == 2)
	{
		if (u.y < 0)
			ra = -1;
		else if (u.y > 0)
			ra = 1;
		else
			ra = 0;
		norm = vec_scalar_ret(ra / u.caca, &u.ca);
	}
	vec_normalize(&norm);
	return (norm);
}

t_closest	check_intersection(t_utcylinder u, t_closest ret, t_dv *rd)
{
	u.y = u.caoc + u.t * u.card;
	if (u.y > 0 && u.y < u.caca)
	{
		ret.t = u.t;
		ret.norm = get_norm(u, rd, u.ra, 1);
		return (ret);
	}
	if (u.y < 0)
		u.t = (0 - u.caoc) / u.card;
	else
		u.t = (u.caca - u.caoc) / u.card;
	if (fabs(u.b + u.a * u.t) < u.h)
	{
		ret.t = u.t;
		ret.norm = get_norm(u, rd, u.ra, 2);
		return (ret);
	}
	return (ret);
}

t_closest	in_out_cyl(t_closest ret, t_utcylinder u, t_cylinder *cy, t_dv *rd)
{
	if (cy->c == 1 || cy->c == -1 || cy->c == 0)
	{
		if (u.t > 0)
			return (check_intersection(u, ret, rd));
		u.t = (u.h - u.b) / u.a;
		return (check_intersection(u, ret, rd));
	}
	else if (cy->c == 2)
		return (check_intersection(u, ret, rd));
	return (ret);
}

t_closest	cyl_intersect(t_dv *ro, t_dv *rd, t_cylinder *cy, t_closest ret)
{
	t_utcylinder	u;

	u.pa = cy->pos;
	u.ra = cy->diam * 0.5;
	u.pb = cy->pb;
	u.ca = vec_substract(&u.pb, &u.pa);
	u.oc = vec_substract(ro, &u.pa);
	u.caca = vec_dot_product(&u.ca, &u.ca);
	u.card = vec_dot_product(&u.ca, rd);
	u.caoc = vec_dot_product(&u.ca, &u.oc);
	u.a = u.caca - u.card * u.card;
	u.b = u.caca * vec_dot_product(&u.oc, rd) - u.caoc * u.card;
	u.c = u.caca * vec_dot_product(&u.oc, &u.oc) - u.caoc * u.caoc
		- u.ra * u.ra * u.caca;
	u.h = u.b * u.b - u.a * u.c;
	if (u.h < 0)
		return (ret);
	u.h = sqrt(u.h);
	u.t = (-1) * (u.b + u.h) / u.a;
	return (in_out_cyl(ret, u, cy, rd));
}
