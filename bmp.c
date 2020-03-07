/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:52:57 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 11:19:26 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int write_header(int fd, t_index *idx)
{
    char header[54];
    int  tmp;
    int file_size;

    ft_bzero(header, 54);
    file_size = 14 + 40 + (idx->el.resolution_x * idx->el.resolution_y) * 4;
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
    header[10] = (unsigned char)(54);
    header[14] = (unsigned char)(40);
    tmp = idx->el.resolution_x;
    header[18] = (unsigned char)(tmp);
    header[19] = (unsigned char)(tmp >> 8);
    header[20] = (unsigned char)(tmp >> 16);
    header[21] = (unsigned char)(tmp >> 24);
    tmp = -idx->el.resolution_y;
    header[22] = (unsigned char)(tmp);
    header[23] = (unsigned char)(tmp >> 8);
    header[24] = (unsigned char)(tmp >> 16);
    header[25] = (unsigned char)(tmp >> 24);
    header[26] = (unsigned char)(1);
    header[28] = (unsigned char)(32);
    write(fd, header, 54);
    return (1);
}

int write_data(int fd, t_index *idx)
{
    char *tmp;

    tmp = (char *)idx->img.addr; 
    write (fd, tmp, (idx->el.resolution_x * idx->el.resolution_y * 4));
    return (1);
}

int screen_shot(t_index *idx)
{
    int     fd;

    if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | S_IRWXU)) < 0)
		return (0);
    if (!write_header(fd, idx))
		return (0);
    if (!write_data(fd, idx))
        return (0);
	close(fd);
    free_all(idx, -1);
    return (1);
}
