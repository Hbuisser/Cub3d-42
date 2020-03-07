/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 11:26:42 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// allowed fct : open, close, read, write, malloc, free, perror, strerror, exit

void verLine(int i, t_index *idx)
{
    int j;
    int k;
    int y;

    j = 0;
    y = idx->big.drawStart;
    while (j < y)
    {
        idx->img.addr[j * idx->el.resolution_x + i] = idx->el.c_color_hex;
        j++;
    }
    while (y < idx->big.drawEnd)
    {
        idx->tex.texY = (int)idx->tex.texPos & (idx->tex.texHeight - 1);
		idx->tex.texPos += idx->tex.step;
        idx->img.addr[y * idx->el.resolution_x + i] = idx->tex.color[idx->tex.texY * idx->tex.texHeight + idx->tex.texX];
        y++;
    }
    k = y;
    while (k < idx->el.resolution_y)
    {
        idx->img.addr[k * idx->el.resolution_x + i] = idx->el.f_color_hex;
        k++;
    }
}

int transform_to_hex(int r, int g, int b)
{
    return (r<<16 | g<<8 | b);
}

void create_algo(t_index *idx)
{
    int		i;
    int		hit;

    i = 0;
    hit = 0;
    while (i < idx->el.resolution_x)
    {
        hit = 0;
        calculate_ray_and_deltaDist(i, idx);
        calculate_step_and_sideDist(idx);
        perform_dda(hit, idx);
        calculate_dist(idx);
        calculate_height_wall(idx);
        calculate_textures(idx);
        calculate_colors(idx);
        verLine(i, idx);
        idx->spr.ZBuffer[i] = idx->big.perpWallDist;
        i++;
    }
    sprites_raycasting(idx);
    mlx_put_image_to_window(idx->window.mlx_ptr, idx->window.mlx_win, idx->img.img, 0, 0);
}

int create_data(t_index *idx)
{
    idx->big.posX = idx->parse.pos_x_init;
    idx->big.posY = idx->parse.pos_y_init;
    if (idx->parse.dir == 'E')
    {
        idx->big.planeX = 0;
        idx->big.planeY = 1.4;
        idx->big.dirX = 1;
        idx->big.dirY = 0;
    }
    else if (idx->parse.dir == 'W')
    {
        idx->big.planeX = 0;
        idx->big.planeY = -1.4;
        idx->big.dirX = -1;
        idx->big.dirY = 0;
    }
    else if (idx->parse.dir == 'S')
    {
        idx->big.planeX = -1.4;
        idx->big.planeY = 0;
        idx->big.dirX = 0;
        idx->big.dirY = 1;
    }
    else if (idx->parse.dir == 'N')
    {
        idx->big.planeX = 1.4;
        idx->big.planeY = 0;
        idx->big.dirX = 0;
        idx->big.dirY = -1;
    }
    idx->tex.texWidth = 64;
    idx->tex.texHeight = 64;
    idx->spr.sprWidth = 0;
    idx->spr.sprHeight = 0;
    idx->big.moveSpeed = 0.2;
    idx->big.rotSpeed = 0.2;
    if (!(idx->spr.ZBuffer = malloc(sizeof(float *) * idx->el.resolution_x + 1)))
        return (-1);
    return (1);
}

int launch_program(t_index *idx, char *av)
{
    create_init(idx);
    if (parse_cub(idx, av) < 0)
        return (-1);
    if (!(idx->window.mlx_ptr = mlx_init()))
        return (-1);
    idx->window.mlx_win = mlx_new_window(idx->window.mlx_ptr, idx->el.resolution_x, idx->el.resolution_y, WINDOW_TITLE);
    create_data(idx);
    generate_textures(idx);
    idx->img.img = mlx_new_image(idx->window.mlx_ptr, idx->el.resolution_x, idx->el.resolution_y);
    idx->img.addr = (int *)mlx_get_data_addr(idx->img.img, &idx->img.bits_per_pixel, &idx->img.line_length, &idx->img.endian);
    create_algo(idx);
    return (1);
}

int main(int ac, char **av)
{
    t_index		idx;
    
    if (ac < 2)
		return (-1);
    else if (ac == 2)
    {
        launch_program(&idx, av[1]);
        mlx_hook(idx.window.mlx_win, 2, 1L<<1, ft_key, &idx);
        mlx_hook(idx.window.mlx_win, 17, 0, exit_all, &idx);
        mlx_loop(idx.window.mlx_ptr);
    }
    else if (ac == 3 && !ft_strncmp(av[2], "--save", 5))
    {
        launch_program(&idx, av[1]);
        screen_shot(&idx);
    }
    return (0);
}
