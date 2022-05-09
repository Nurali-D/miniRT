/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:07:29 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 23:00:19 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_dv	canv_to_viewport(int x, int y)
{
	t_dv	dot;
	float	alpha;
	float	ratio;

	ratio = (float)g_scene->res.x / (float)g_scene->res.y;
	alpha = (float)g_scene->cam->fov * 0.5 * M_PI / 180;
	dot.x = (x + 0.5) * (2.0 * tan(alpha)) / (float)g_scene->res.x;
	dot.y = (y + 0.5) * (2.0 * tan(alpha) / ratio) / (float)g_scene->res.y;
	dot.z = 1;
	return (dot);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_len + x * (data->b_p_pix / 8));
	*(unsigned int *)dst = color;
}

void	ray_tracing(void *mlx, t_img *img)
{
	t_dv	dot_d;
	int		x;
	int		y;
	int		color;

	x = (g_scene->res.x * 0.5) * (-1);
	img->img = mlx_new_image(mlx, g_scene->res.x, g_scene->res.y);
	img->addr =
	mlx_get_data_addr(img->img, &img->b_p_pix, &img->line_len, &img->endian);
	while (x < g_scene->res.x * 0.5)
	{
		y = g_scene->res.y * 0.5;
		while (y > ((g_scene->res.y * 0.5) * (-1)))
		{
			dot_d = canv_to_viewport(x, y);
			rotate_cam(&dot_d, g_scene->cam);
			color = get_pixel_color(&g_scene->cam->pos, &dot_d);
			my_mlx_pixel_put(img, (int)(g_scene->res.x * 0.5 + x),
			(int)(g_scene->res.y * 0.5 - y), color);
			y--;
		}
		x++;
	}
}
