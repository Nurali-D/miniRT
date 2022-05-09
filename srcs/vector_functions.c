/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 23:50:16 by ltulune           #+#    #+#             */
/*   Updated: 2021/03/05 03:10:48 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dv	vec_substract(t_dv *v1, t_dv *v2)
{
	t_dv	res;

	res.x = v1->x - v2->x;
	res.y = v1->y - v2->y;
	res.z = v1->z - v2->z;
	return (res);
}

float	vec_length(t_dv *vec)
{
	float	res;

	res = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	return (res);
}

void	vec_normalize(t_dv *vec)
{
	float	len;

	len = 1 / vec_length(vec);
	vec->x *= len;
	vec->y *= len;
	vec->z *= len;
}

float	vec_dot_product(t_dv *v1, t_dv *v2)
{
	float	res;

	res = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (res);
}

t_dv	vec_sum(t_dv *v1, t_dv *v2)
{
	t_dv	sum;

	sum.x = v1->x + v2->x;
	sum.y = v1->y + v2->y;
	sum.z = v1->z + v2->z;
	return (sum);
}
