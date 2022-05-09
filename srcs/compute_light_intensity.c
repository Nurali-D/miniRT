/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light_intensity.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:07:06 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/04 16:37:54 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		diffuse_intens(t_closest cl, t_dv *l_vec, float light_i)
{
	float	n_dot;
	float	i;

	i = 0;
	n_dot = vec_dot_product(&cl.norm, l_vec);
	if (n_dot > 0)
		i = light_i * n_dot / (vec_length(&cl.norm) * vec_length(l_vec));
	return (i);
}

float		spec_intens(t_closest cl, t_dv *l_vec, t_dv *vec_d, float light_i)
{
	t_dv	vec_v;
	float	dot_v;
	t_dv	tmp;
	t_dv	vec_r;

	vec_v = *vec_d;
	vec_scalar(-1, &vec_v);
	dot_v = 2 * vec_dot_product(&cl.norm, l_vec);
	tmp = cl.norm;
	vec_scalar(dot_v, &tmp);
	vec_r = vec_substract(&tmp, l_vec);
	dot_v = vec_dot_product(&vec_r, &vec_v);
	if (dot_v > 0)
	{
		dot_v = light_i *
		pow(dot_v / (vec_length(&vec_r) * vec_length(&vec_v)), 300);
		return (dot_v);
	}
	return (0);
}

float		compute_i(t_closest cl, t_dv *vec_d, t_dv *l_vec, t_light *lgt)
{
	float		i;
	t_closest	tl;

	i = 0;
	tl = closest_intersection(&cl.p_dot, l_vec, 0.0001, 1);
	if (tl.t != INFINITY)
		return (i);
	i += diffuse_intens(cl, l_vec, lgt->ratio);
	i += spec_intens(cl, l_vec, vec_d, lgt->ratio);
	return (i);
}
