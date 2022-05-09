/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 01:33:18 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 15:41:45 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../lib/libft/libft.h"
# include "mlx.h"
# include "mlx_mms.h"
# include "elements.h"
# include "scene.h"
# include "get_next_line.h"

# define HEADER_SIZE 120
# define OPEN_ERROR -1
# define CLOSE_ERROR -2
# define PARSE_ERROR -3
# define MLX_ERROR -4
# define MALLOC_ERROR -5
# define INPUT_ERROR -6
# define THREAD_ERROR -7

t_scene			*g_scene;

t_closest		intersect_sp(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim);
t_closest		closest_intersection(t_dv *dot_o, t_dv *vec_d, float min,
																float max);
t_closest		intersect_pl(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim);
t_closest		intersect_tr(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim);
t_closest		intersect_sq(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim);
t_closest		intersect_cy(t_dv *dot_o, t_dv *dot_d, void *data, t_root lim);
t_closest		cyl_intersect(t_dv *ro, t_dv *rd, t_cylinder *cy,
								t_closest ret);
t_camera		*parse_camera(char *line, t_camera *cam);
t_light			*parse_light(char *line, t_light *lgt);
t_dv			vec_substract(t_dv *v1, t_dv *v2);
t_dv			vec_sum(t_dv *v1, t_dv *v2);
t_dv			vec_cross(t_dv v1, t_dv v2);
t_dv			vec_scalar_ret(float n, t_dv *vec);
t_dv			new_vector(float x, float y, float z);
t_dv			mix_col(t_dv *c1, t_dv *c2);
int				handle_key(int k, t_window *w);
int				exit_program(void);
int				rgb_to_int(t_dv *color);
int				get_pixel_color(t_dv *dot_o, t_dv *dot_d);
float			ft_atof(char *str);
float			vec_length(t_dv *vec);
float			vec_dot_product(t_dv *v1, t_dv *v2);
float			compute_i(t_closest cl, t_dv *vec_d, t_dv *l_vec, t_light *lgt);
float			len_ab(t_dv *a, t_dv *b);
char			*get_color(char *line, t_dv *color);
char			*get_position(char *line, t_dv *pos);
char			*get_ori(char *line, t_dv *ori);
char			*create_bmp_fname(char *file, int i);
void			parse_amb_light(char *line, t_alight *al);
void			parse_resolution(char *line, t_resolution *res);
void			parse_scene(int argc, char **argv, t_window *w);
void			parse_plane(char *line);
void			parse_sphere(char *line);
void			parse_square(char *line);
void			parse_cylinder(char *line);
void			parse_triangle(char *line);
void			print_error_exit(char *str, int err);
void			vec_normalize(t_dv *vec);
void			vec_scalar(float n, t_dv *vec);
void			vec_p_dot(t_dv *v1, t_dv *v2, t_dv *v3, float n);
void			ray_tracing(void *mlx, t_img *img);
void			invert_normal(t_dv *norm, t_dv p, t_dv *o);
void			create_bmp(char *filename, t_window *w);
void			init_ret(t_closest *ret);
void			rotate_cam(t_dv *dot, t_camera *cam);
void			*get_pixel_color_bon(void *arg);
void			free_scene(void);

#endif
