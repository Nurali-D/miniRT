/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 18:48:38 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 18:57:18 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dv	new_vector(float x, float y, float z)
{
	t_dv	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vec_scalar(float n, t_dv *vec)
{
	vec->x *= n;
	vec->y *= n;
	vec->z *= n;
}

t_dv	vec_scalar_ret(float n, t_dv *vec)
{
	t_dv	ret;

	ret.x = vec->x * n;
	ret.y = vec->y * n;
	ret.z = vec->z * n;
	return (ret);
}

void	vec_p_dot(t_dv *v1, t_dv *v2, t_dv *v3, float n)
{
	v1->x = v2->x + n * v3->x;
	v1->y = v2->y + n * v3->y;
	v1->z = v2->z + n * v3->z;
}

t_dv	vec_cross(t_dv v1, t_dv v2)
{
	t_dv	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}
