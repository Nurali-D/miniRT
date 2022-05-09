/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:57:55 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 21:29:11 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define KEYCODE_Q 12
# define KEYCODE_E 14
# define KEYCODE_A 0
# define KEYCODE_D 2
# define KEYCODE_S 1
# define KEYCODE_W 13
# define KEYCODE_R 15
# define KEYCODE_F 3
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_UP 125
# define KEYCODE_DOWN 126
# define KEYCODE_1 84
# define KEYCODE_2 83

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		b_p_pix;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_window
{
	t_mlx		*pt;
	t_img		img;
}				t_window;

typedef struct	s_scene
{
	t_resolution	res;
	t_alight		al;
	t_camera		*cam;
	t_light			*lgt;
	t_object		*obj;
	t_window		*w;
}				t_scene;

#endif
