/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:37:54 by ltulune           #+#    #+#             */
/*   Updated: 2021/02/17 06:55:42 by ltulune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				check_rem_for_bsn(char **r, char **l)
{
	char		*bsn;
	char		*tmp;

	if (*r && (bsn = ft_strchr(*r, '\n')))
	{
		*bsn = '\0';
		if (!(*l = ft_strjoin_mod(*l, *r)))
			return (-1);
		bsn++;
		if (!(tmp = ft_strdup(bsn)))
			return (-1);
		free(*r);
		*r = tmp;
		return (1);
	}
	return (0);
}

int				save_and_return(int fd, char **line, char **rem, char *buf)
{
	int			n_buf;
	char		*tmp;

	while ((n_buf = read(fd, buf, BUFFER_SIZE)))
	{
		if ((buf[n_buf] = '\0') == '\0'
		&& !(tmp = ft_strjoin_mod(*rem, buf)))
			return (-1);
		free(*rem);
		if ((*rem = tmp) && (check_rem_for_bsn(rem, line)) == 1)
			return (1);
		else if (check_rem_for_bsn(rem, line) == -1)
			return (-1);
	}
	if (!*line && !*rem)
	{
		if (!(*line = (char*)malloc(sizeof(char))))
			return (-1);
		*line[0] = '\0';
	}
	else if (!(*line = ft_strjoin_mod(*line, *rem)) || n_buf < 0)
		return (-1);
	free(*rem);
	*rem = NULL;
	return (0);
}

int				get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*rem;

	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0) || BUFFER_SIZE < 1
	|| BUFFER_SIZE > 8200000)
		return (-1);
	*line = NULL;
	if (check_rem_for_bsn(&rem, line) == 1)
		return (1);
	else if (check_rem_for_bsn(&rem, line) == -1)
		return (-1);
	return (save_and_return(fd, line, &rem, buf));
}
