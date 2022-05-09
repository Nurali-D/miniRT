/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:35:22 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 19:20:31 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		rgb_to_int(t_dv *color)
{
	int	r;
	int	g;
	int	b;

	r = color->x;
	g = color->y;
	b = color->z;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

t_dv	mix_col(t_dv *c1, t_dv *c2)
{
	t_dv	mix;

	mix.x = c1->x * c2->x / 255;
	mix.y = c1->y * c2->y / 255;
	mix.z = c1->z * c2->z / 255;
	return (mix);
}

float	len_ab(t_dv *a, t_dv *b)
{
	return (sqrt(pow((a->x - b->x), 2) + pow((a->y - b->y), 2)
			+ pow((a->z - b->z), 2)));
}
