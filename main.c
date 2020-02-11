/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/11 14:07:59 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// allowed fct : open, close, read, write, malloc, free, perror, strerror, exit

void verLine(int i, t_index *idx, int *data)
{
    int j;
    int k;
    int y;

    j = 0;
    y = idx->big->drawStart;
    while (j < y)
    {
        data[j * idx->el->resolution_x + i] = idx->el->c_color_hex;
        j++;
    }
    while (y < idx->big->drawEnd)
    {
        data[y * idx->el->resolution_x + i] = idx->big->color_n[idx->big->texY * 64 + idx->big->texX];
        y++;
    }
    k = y + 1;
    while (k < idx->el->resolution_y)
    {
        data[k * idx->el->resolution_x + i] = idx->el->f_color_hex;
        k++;
    }
}

void	calculate_textures(t_index *idx)
{
    int		texNum;
    double	wallX;
	double	step;
	double 	texPos;
	int 	y;

    //the value of the current map square minus 1, 
    //the reason is that there exists a texture 0, but map tile 0 has no texture since it represents an empty space
    texNum = idx->parse->map[idx->big->mapY][idx->big->mapX] - 1;
    //wallX represents the exact value where the wall was hit
    if (idx->big->side == 0) 
        wallX = idx->big->posY + idx->big->perpWallDist * idx->big->rayDirY;
    else
        wallX = idx->big->posX + idx->big->perpWallDist * idx->big->rayDirX;
    wallX -= floor((wallX));

    //x coordinate on the texture
    idx->big->texX = (int)(wallX * (double)(idx->big->texWidth));
    if (idx->big->side == 0 && idx->big->rayDirX > 0) 
		idx->big->texX = idx->big->texWidth - idx->big->texX - 1;
    if (idx->big->side == 1 && idx->big->rayDirY < 0) 
		idx->big->texX = idx->big->texWidth - idx->big->texX - 1;
	
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * idx->big->texHeight / idx->big->lineHeight;
	// Starting texture coordinate
	texPos = (idx->big->drawStart - idx->el->resolution_y / 2 + idx->big->lineHeight / 2) * step;

	y = idx->big->drawStart;
	while (y < idx->big->drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		idx->big->texY = (int)texPos & (idx->big->texHeight - 1);
		texPos += step;
		y++;
	}
}

void calculate_height_wall(t_index *idx)
{
    idx->big->wallHeight = idx->el->resolution_y * 0.6;
    idx->big->lineHeight = (int)(idx->big->wallHeight / idx->big->perpWallDist);
    idx->big->drawStart = -idx->big->lineHeight / 2 + idx->el->resolution_y / 2;
    if (idx->big->drawStart < 0)
        idx->big->drawStart = 0;
    idx->big->drawEnd = idx->big->lineHeight / 2 + idx->el->resolution_y / 2;
    if (idx->big->drawEnd >= idx->el->resolution_y)
        idx->big->drawEnd = idx->el->resolution_y - 1;
}

void calculate_dist(t_index *idx)
{
    if (idx->big->side == 0)
        idx->big->perpWallDist = (idx->big->mapX - idx->big->posX +
        (1 - idx->big->stepX) / 2) / idx->big->rayDirX;
    else 
        idx->big->perpWallDist = (idx->big->mapY - idx->big->posY +
        (1 - idx->big->stepY) / 2) / idx->big->rayDirY;
}

void perform_dda(int hit, t_index *idx)
{
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (idx->big->sideDistX < idx->big->sideDistY)
        {
            idx->big->sideDistX += idx->big->deltaDistX;
            idx->big->mapX += idx->big->stepX;
            idx->big->side = 0;
        }
        else
        {
            idx->big->sideDistY += idx->big->deltaDistY;
            idx->big->mapY += idx->big->stepY;
            idx->big->side = 1;
        }
        if (idx->parse->map[idx->big->mapY][idx->big->mapX] > '0') 
            hit = 1;
    }
    // if side blabla 4 coins
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

int generate_textures(t_index *idx)
{
    //printf("%s\n", idx->el->n_path);
    if (!(idx->big->color_n = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->n_path, &idx->big->texWidth, &idx->big->texHeight)))
    {
        write (1, "nwrong path texture", 18);
        return (-1);
    }
	if (!(idx->big->color_s = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->s_path, &idx->big->texWidth, &idx->big->texHeight)))
    {
        write (1, "swrong path texture", 18);
        return (-1);
    }
	if (!(idx->big->color_w = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->w_path, &idx->big->texWidth, &idx->big->texHeight)))
    {
        write (1, "wwrong path texture", 18);
        return (-1);
    }
	if (!(idx->big->color_e = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->e_path, &idx->big->texWidth, &idx->big->texHeight)))
    {
        write (1, "ewrong path texture", 18);
        return (-1);
    }
    return (0);
}

void create_algo(t_index *idx)
{
    int		i;
    int		hit;

    i = 0;
    hit = 0;
    while (i < idx->el->resolution_x)
    {
        hit = 0;
        calculate_ray_and_deltaDist(i, idx);
        calculate_step_and_sideDist(idx);
        perform_dda(hit, idx);
        calculate_dist(idx);
        calculate_height_wall(idx);
        generate_textures(idx);
        calculate_textures(idx);
        verLine(i, idx, idx->img->addr);
        i++;
    }
    mlx_put_image_to_window(idx->window->mlx_ptr, idx->window->mlx_win, idx->img->img, 0, 0);
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
    if (!(idx->window->mlx_ptr = mlx_init()))
        return (-1);
    idx->window->mlx_win = mlx_new_window(idx->window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y, WINDOW_TITLE);
    create_settings(idx);
    idx->img->img = mlx_new_image(idx->window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y);
    idx->img->addr = (int*)mlx_get_data_addr(idx->img->img, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    create_algo(idx);
    mlx_hook(idx->window->mlx_win, 2, 1L<<1, ft_key, idx);
    mlx_loop(idx->window->mlx_ptr);
    return (0);
}
