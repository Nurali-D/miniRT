/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:08:08 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 16:05:32 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		check_rt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 't' || str[i - 2] != 'r' || str[i - 3] != '.'
		|| !(ft_isdigit(str[i - 4]) || ft_isalpha(str[i - 4])))
		return (0);
	return (1);
}

void	start_window(t_window *w)
{
	mlx_clear_window(w->pt->mlx_ptr, w->pt->win_ptr);
	mlx_put_image_to_window(w->pt->mlx_ptr, w->pt->win_ptr, w->img.img, 0, 0);
	mlx_hook(w->pt->win_ptr, 2, 1L << 0, handle_key, w);
	mlx_hook(w->pt->win_ptr, 17, 1L << 17, exit_program, 0);
	mlx_loop(w->pt->mlx_ptr);
}

void	check_resolution(t_mlx *mlx_ptr)
{
	int	width;
	int	height;

	mlx_get_screen_size(mlx_ptr, &width, &height);
	if (g_scene->res.x > width)
		g_scene->res.x = width;
	if (g_scene->res.y > height)
		g_scene->res.y = height;
}

int		main(int argc, char **argv)
{
	t_window	w;
	t_mlx		pt;

	g_scene = NULL;
	if (argc < 2 || argc > 3)
		print_error_exit("invalid input", INPUT_ERROR);
	if ((check_rt(argv[1])) == 0)
		print_error_exit("invalid input", INPUT_ERROR);
	w.pt = &pt;
	w.pt->win_ptr = NULL;
	w.pt->mlx_ptr = mlx_init();
	parse_scene(argc, argv, &w);
	check_resolution(w.pt->mlx_ptr);
	w.pt->win_ptr = mlx_new_window(w.pt->mlx_ptr, g_scene->res.x,
									g_scene->res.y, "miniRT");
	ray_tracing(w.pt->mlx_ptr, &w.img);
	if (argc == 2)
		start_window(&w);
	else if (argc == 3 && !(ft_strcmp(argv[2], "--save")))
		create_bmp(create_bmp_fname(argv[1], ft_strlen(argv[1]) - 3), &w);
	else
		print_error_exit("invalid input", INPUT_ERROR);
	return (0);
}
