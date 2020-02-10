/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/10 15:22:30 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// allowed fct : open, close, read, write, malloc, free, perror, strerror, exit

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void verLine(int i, t_index *idx, int side)
{
    int color;
    int j;
    int k;

    j = 0;
    if (side == 1)
        color = 0xffffff;
    else 
        color = 0x0000ff;
    while (j < idx->big->drawStart)
    {
        mlx_pixel_put(idx->window->mlx_ptr, idx->window->mlx_win, i, j, idx->el->c_color_hex);
        j++;
    }
    while (idx->big->drawStart < idx->big->drawEnd)
    {
        //my_mlx_pixel_put(img, drawEnd, drawStart, color);
        mlx_pixel_put(idx->window->mlx_ptr, idx->window->mlx_win, i, idx->big->drawStart, color);
        idx->big->drawStart++;
    }
    k = idx->big->drawStart + 1;
    while (k < idx->el->resolution_y)
    {
        mlx_pixel_put(idx->window->mlx_ptr, idx->window->mlx_win, i, k, idx->el->f_color_hex);
        k++;
    }
}

void calculate_height_wall(t_index *idx)
{
    int lineHeight;
    int wallHeight;
    
    wallHeight = idx->el->resolution_y * 0.6;
    lineHeight = (int)(wallHeight / idx->big->perpWallDist);
    idx->big->drawStart = -lineHeight / 2 + idx->el->resolution_y / 2;
    if (idx->big->drawStart < 0)
        idx->big->drawStart = 0;
    idx->big->drawEnd = lineHeight / 2 + idx->el->resolution_y / 2;
    if (idx->big->drawEnd >= idx->el->resolution_y)
        idx->big->drawEnd = idx->el->resolution_y - 1;
}

void calculate_dist(t_index *idx, int side)
{
    if (side == 0)
        idx->big->perpWallDist = (idx->big->mapX - idx->big->posX +
        (1 - idx->big->stepX) / 2) / idx->big->rayDirX;
    else 
        idx->big->perpWallDist = (idx->big->mapY - idx->big->posY +
        (1 - idx->big->stepY) / 2) / idx->big->rayDirY;
}

int perform_dda(int hit, t_index *idx)
{
    int side;
    
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (idx->big->sideDistX < idx->big->sideDistY)
        {
            idx->big->sideDistX += idx->big->deltaDistX;
            idx->big->mapX += idx->big->stepX;
            side = 0;
        }
        else
        {
            idx->big->sideDistY += idx->big->deltaDistY;
            idx->big->mapY += idx->big->stepY;
            side = 1;
        }
        if (idx->parse->map[idx->big->mapY][idx->big->mapX] > '0') 
            hit = 1;
    }
    return (side);
}

void calculate_step_and_sideDist(t_index *idx)
{
    if (idx->big->rayDirX < 0)
    {
        idx->big->stepX = -1;
        idx->big->sideDistX = (idx->big->posX - idx->big->mapX) * idx->big->deltaDistX;
    }
    else
    {
        idx->big->stepX = 1;
        idx->big->sideDistX = (idx->big->mapX + 1.0 - idx->big->posX) * idx->big->deltaDistX;
    }
    if (idx->big->rayDirY < 0)
    {
        idx->big->stepY = -1;
        idx->big->sideDistY = (idx->big->posY - idx->big->mapY) * idx->big->deltaDistY;
    }
    else
    {
        idx->big->stepY = 1;
        idx->big->sideDistY = (idx->big->mapY + 1.0 - idx->big->posY) * idx->big->deltaDistY;
    }
}

void calculate_ray_and_deltaDist(int i, t_index *idx)
{
    // x-coordinate in camera space
    idx->big->cameraX = 2 * i / (double)idx->el->resolution_x - 1;
    idx->big->rayDirX = idx->big->dirX + idx->big->planeX * idx->big->cameraX;
    idx->big->rayDirY = idx->big->dirY + idx->big->planeY * idx->big->cameraX;
    // mapX and mapY represent the current square of the map the ray is in
    idx->big->mapX = (int)idx->big->posX;
    idx->big->mapY = (int)idx->big->posY;
    // deltaDistX is the distance the ray has to travel to go from 1 x-side to the next x-side
    idx->big->deltaDistX = fabs(1 / idx->big->rayDirX);
    idx->big->deltaDistY = fabs(1 / idx->big->rayDirY);
}

int transform_to_hex(int r, int g, int b)
{
    return (r<<16 | g<<8 | b);
}

void generate_textures(t_index *idx)
{
    mlx_xpm_file_to_image(idx->window->mlx_ptr, "texture/bluestone.png", &idx->big->texWidth, &idx->big->texHeight);
}

void create_algo(t_index *idx)
{
    int             i;
    int             hit;
    int             side;
    //unsigned int    buffer[idx->big->mapY][idx->big->mapX];
    //int             *texture[8];

    i = 0;
    hit = 0;
    while (i < idx->el->resolution_x)
    {
        hit = 0;
        generate_textures(idx);
        calculate_ray_and_deltaDist(i, idx);
        calculate_step_and_sideDist(idx);
        side = perform_dda(hit, idx);
        calculate_dist(idx, side);
        calculate_height_wall(idx);
        verLine(i, idx, side);
        i++;
    }
}

void create_settings(t_index *idx)
{
    idx->big->posX = idx->parse->posX;
    idx->big->posY = idx->parse->posY;
    idx->big->dirX = -1;
    idx->big->dirY = 0;
    idx->big->planeX = 0;
    idx->big->planeY = 0.66;
    idx->big->texWidth = 64;
    idx->big->texHeight = 64;
}

int main(int ac, char **av)
{
    t_index		*idx = malloc(sizeof(t_index));
    t_window	*window = malloc(sizeof(t_window));
    t_image		*img = malloc(sizeof(t_image));
    t_big		*big = malloc(sizeof(t_big));
    t_parse     *parse = malloc(sizeof(t_parse));
    t_elements  *el = malloc(sizeof(t_elements));

	if (ac < 2)
		return (-1);

    idx->big = big;
    idx->img = img;
    idx->parse = parse;
    idx->el = el;
    idx->window = window;

	if (parse_cub(idx, av[1]) < 0)
        return (-1);
        
    if (!(window->mlx_ptr = mlx_init()))
        return (-1);
    window->mlx_win = mlx_new_window(window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y, WINDOW_TITLE);
    mlx_hook(window->mlx_win, 2, 1L<<1, ft_key, idx);
    //img.img = mlx_new_image(window.mlx_ptr, idx.el->resolution_x, idx.el->resolution_y);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    create_settings(idx);
    create_algo(idx);
    //mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, img.img, 0, 0);
    mlx_loop(window->mlx_ptr);
    return (0);
}
