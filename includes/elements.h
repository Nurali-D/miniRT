/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:48:08 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/07 20:46:31 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENTS_H
# define ELEMENTS_H

typedef struct	s_dv
{
	float	x;
	float	y;
	float	z;
}				t_dv;

typedef struct	s_sphere
{
	t_dv			pos;
	float			diam;
	t_dv			color;
}				t_sphere;

typedef struct	s_plane
{
	t_dv			pos;
	t_dv			ori;
	t_dv			color;
}				t_plane;

typedef struct	s_square
{
	t_dv			pos;
	t_dv			ori;
	float			size;
	t_dv			color;
}				t_square;

typedef struct	s_squtils
{
	t_dv	ca;
	t_dv	cp;
	t_dv	ap;
	t_dv	ac;
	float	pn;
}				t_squtils;

typedef struct	s_cylinder
{
	t_dv				pos;
	t_dv				ori;
	t_dv				pb;
	float				diam;
	float				height;
	t_dv				color;
	int					c;
}				t_cylinder;

typedef struct	s_utcylinder
{
	t_dv	ca;
	t_dv	oc;
	t_dv	pa;
	t_dv	pb;
	float	ra;
	float	caca;
	float	card;
	float	caoc;
	float	a;
	float	b;
	float	c;
	float	h;
	float	y;
	float	t;
}				t_utcylinder;

typedef struct	s_triangle
{
	t_dv				pnt1;
	t_dv				pnt2;
	t_dv				pnt3;
	t_dv				color;
}				t_triangle;

typedef struct	s_trutils
{
	t_dv				v1;
	t_dv				v2;
	t_dv				vec_t;
	t_dv				vec_p;
	float				det;
	float				a;
	float				b;
	float				c;
}				t_trutils;

typedef struct	s_resolution
{
	int	x;
	int	y;
}				t_resolution;

typedef struct	s_alight
{
	float	ratio;
	t_dv	color;
}				t_alight;

typedef struct	s_light
{
	t_dv			pos;
	float			ratio;
	t_dv			color;
	struct s_light	*next;
}				t_light;

typedef struct	s_camera
{
	t_dv			pos;
	t_dv			ori;
	int				fov;
	struct s_camera	*next;
	struct s_camera	*prev;
}				t_camera;

typedef struct	s_root
{
	float t1;
	float t2;
}				t_root;

typedef struct	s_closest
{
	float	t;
	t_dv	p_dot;
	t_dv	norm;
	t_dv	color;
	int		col;
}				t_closest;

typedef struct	s_object
{
	t_closest	(*intersect_funct)(t_dv *dot_o,
					t_dv *dot_d, void *data, t_root lim);
	void		*data;
	void		*next;
}				t_object;

typedef struct	s_matrix
{
	t_dv	forw;
	t_dv	right;
	t_dv	up;
	t_dv	orig;
}				t_matrix;

#endif
