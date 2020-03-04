/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:52:57 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/04 12:30:01 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*int write_header(int fd, int file_size, int first_pix, t_index *idx)
{
    char header[54];
    int  file_size;
	//bpp = 32

    ft_bzero(header);
    file_size = 14 + 40 + (idx->el->resolution_x * idx->el->resolution_y) * 4;
    header[0] = 'B';
    header[1] = 'M';

	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);

    write(fd, &file_size, 4);
    write(fd, "\0\0\0\0", 4);
    write (fd, &first_pix, 4);
    write(fd, &header_info_size, 4);
	write(fd, &idx->el->resolution_x, 4);
	write(fd, &idx->el->resolution_y, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &idx->img->bits_per_pixel, 2);*/
    /*return (1);
}

int screen_shot(t_index *idx)
{
    int     fd;

    if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR | S_IRWXU)) < 0)
		    return (0);
    if (!write_header(fd, file_size, first_pix, idx))
		    return (0);
	
    return (1);
}*/
