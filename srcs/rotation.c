/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:18:24 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/05 15:12:22 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dv		multiple_matrix(t_dv *vec, t_matrix *mat)
{
	t_dv	ret;

	ret.x = vec->x * mat->right.x + vec->y * mat->up.x
			+ vec->z * mat->forw.x + mat->orig.x;
	ret.y = vec->x * mat->right.y + vec->y * mat->up.y
			+ vec->z * mat->forw.y + mat->orig.y;
	ret.z = vec->x * mat->right.z + vec->y * mat->up.z
			+ vec->z * mat->forw.z + mat->orig.z;
	return (ret);
}

t_matrix	look_at(t_camera *cam)
{
	t_matrix	mat;
	t_dv		up_tmp;

	mat.forw = cam->ori;
	mat.orig = cam->pos;
	vec_normalize(&mat.forw);
	if (!(mat.forw.x == 0 && (mat.forw.y == 1 || mat.forw.y == -1)
		&& mat.forw.z == 0))
		up_tmp = new_vector(0, 1, 0);
	else if (mat.forw.x == 0 && mat.forw.y == 1 && mat.forw.z == 0)
		up_tmp = new_vector(0, 0, -1);
	else if (mat.forw.x == 0 && mat.forw.y == -1 && mat.forw.z == 0)
		up_tmp = new_vector(0, 0, 1);
	mat.right = vec_cross(up_tmp, mat.forw);
	vec_normalize(&mat.right);
	mat.up = vec_cross(mat.forw, mat.right);
	vec_normalize(&mat.up);
	return (mat);
}

void		rotate_cam(t_dv *dot, t_camera *cam)
{
	t_matrix	mat;
	t_dv		ray;

	mat = look_at(cam);
	ray = multiple_matrix(dot, &mat);
	ray = vec_substract(&ray, &cam->pos);
	vec_normalize(&ray);
	*dot = ray;
}
