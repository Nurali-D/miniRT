/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:35:16 by ltulune           #+#    #+#             */
/*   Updated: 2021/04/08 15:17:16 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_pixels_data(char **bmp_data, t_window *w)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = g_scene->res.y;
	while (y--)
	{
		x = -1;
		while (++x < g_scene->res.x)
		{
			j = (x * (w->img.b_p_pix / 8)) + (y * w->img.line_len);
			*(*bmp_data + i++) = *(w->img.addr + j++);
			*(*bmp_data + i++) = *(w->img.addr + j++);
			*(*bmp_data + i++) = *(w->img.addr + j);
		}
	}
}

void	get_header(char **bmp_data)
{
	unsigned int size;

	size = g_scene->res.y * g_scene->res.x * 3;
	*(unsigned short *)*bmp_data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*bmp_data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*bmp_data + 6) = 0u;
	*(unsigned char *)(*bmp_data + 10) = HEADER_SIZE;
	*(unsigned int *)(*bmp_data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*bmp_data + 18) = g_scene->res.x;
	*(unsigned int *)(*bmp_data + 22) = g_scene->res.y;
	*(unsigned short *)(*bmp_data + 26) = 1;
	*(unsigned short *)(*bmp_data + 28) = 24;
	*(unsigned int *)(*bmp_data + 30) = 0;
	*(unsigned int *)(*bmp_data + 34) = (unsigned int)size;
	*(unsigned int *)(*bmp_data + 38) = 3780;
	*(unsigned int *)(*bmp_data + 42) = 3780;
	*(int *)(*bmp_data + 46) = 0;
	*(int *)(*bmp_data + 50) = 0;
}

void	create_bmp(char *fname, t_window *w)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*bmp_data;

	size = g_scene->res.y * g_scene->res.x * 3;
	if (!(bmp_data = malloc((size + HEADER_SIZE) * sizeof(char))))
		print_error_exit("malloc error", MALLOC_ERROR);
	i = 0;
	while (i < size + HEADER_SIZE)
		bmp_data[i++] = 0;
	get_header(&bmp_data);
	get_pixels_data(&bmp_data, w);
	if ((fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		print_error_exit("open error", OPEN_ERROR);
	write(fd, bmp_data, (size + HEADER_SIZE));
	close(fd);
	free(fname);
	free(bmp_data);
	free_scene();
}

char	*create_bmp_fname(char *file, int i)
{
	char		*fname;
	char		*b;
	int			j;
	int			k;

	b = "bmp";
	if (!(fname = malloc(sizeof(char) * (i + 5))))
		print_error_exit("malloc error", MALLOC_ERROR);
	j = -1;
	while (++j <= i)
		fname[j] = file[j];
	k = -1;
	while (++k < 4)
		fname[j + k] = b[k];
	return (fname);
}
