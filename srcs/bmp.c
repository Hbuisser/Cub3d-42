/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:52:57 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/10 10:59:41 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		write_header(int fd, t_index *m, int tmp, int file_size)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(tmp);
	header[19] = (unsigned char)(tmp >> 8);
	header[20] = (unsigned char)(tmp >> 16);
	header[21] = (unsigned char)(tmp >> 24);
	tmp = -m->el.res_y;
	header[22] = (unsigned char)(tmp);
	header[23] = (unsigned char)(tmp >> 8);
	header[24] = (unsigned char)(tmp >> 16);
	header[25] = (unsigned char)(tmp >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
	return (1);
}

int		write_data(int fd, t_index *m)
{
	char *tmp;

	tmp = (char *)m->img.addr;
	write(fd, tmp, (m->el.res_x * m->el.res_y * 4));
	return (1);
}

int		screen_shot(t_index *m)
{
	int	fd;
	int	tmp;
	int	file_size;

	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | S_IRWXU)) < 0)
		return (0);
	tmp = m->el.res_x;
	file_size = 14 + 40 + (m->el.res_x * m->el.res_y) * 4;
	if (!write_header(fd, m, tmp, file_size))
		return (0);
	if (!write_data(fd, m))
		return (0);
	close(fd);
	exit_all(m);
	return (1);
}
