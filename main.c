/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/15 16:03:35 by hbuisser         ###   ########.fr       */
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
    y = idx->big->drawStart;
    while (j < y)
    {
        idx->img->addr[j * idx->el->resolution_x + i] = idx->el->c_color_hex;
        j++;
    }
    while (y < idx->big->drawEnd)
    {
        idx->tex->texY = (int)idx->tex->texPos & (idx->tex->texHeight - 1);
		idx->tex->texPos += idx->tex->step;
        idx->img->addr[y * idx->el->resolution_x + i] = idx->tex->color[idx->tex->texY * idx->tex->texHeight + idx->tex->texX];
        y++;
    }
    k = y + 1;
    while (k < idx->el->resolution_y)
    {
        idx->img->addr[k * idx->el->resolution_x + i] = idx->el->f_color_hex;
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
    //float   ZBuffer[idx->el->resolution_x];
    //int     spriteOrder[idx->spr->numSprites];
    //float   spriteDistance[idx->spr->numSprites];

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
        calculate_colors(idx);
        //ZBuffer[i] = idx->big->perpWallDist;
        verLine(i, idx);
        //SET THE ZBUFFER FOR THE SPRITE CASTING
        //perpendicular distance is used
        //ZBuffer[x] = perpWallDist;
        i++;
    }
    i = 0;
    /*while (i < numSprites)
    {
        spriteOrder[i] = i;
        spriteDistance[i] = ((idx->parse->posX - sprite[i].x) * (idx->parse->posX - sprite[i].x) +
                (idx->parse->posY - sprite[i].y) * (idx->parse->posY - sprite[i].y));
        i++;
    }*/
    //sortSprites(spriteOrder, spriteDistance, idx);
    sprites_raycasting(idx);
    mlx_put_image_to_window(idx->window->mlx_ptr, idx->window->mlx_win, idx->img->img, 0, 0);
}

void create_data(t_index *idx)
{
    idx->big->posX = idx->parse->posX;
    idx->big->posY = idx->parse->posY;
    idx->big->dirX = -1;
    idx->big->dirY = 0;
    idx->big->planeX = 0;
    idx->big->planeY = 0.66;
    idx->tex->texWidth = 64;
    idx->tex->texHeight = 64;
    idx->spr->sprWidth = 0;
    idx->spr->sprHeight = 0;
}

int main(int ac, char **av)
{
    t_index		*idx = malloc(sizeof(t_index));
    t_window	*window = malloc(sizeof(t_window));
    t_image		*img = malloc(sizeof(t_image));
    t_big		*big = malloc(sizeof(t_big));
    t_parse     *parse = malloc(sizeof(t_parse));
    t_elements  *el = malloc(sizeof(t_elements));
    t_tex       *tex = malloc(sizeof(t_tex));
    t_spr       *spr = malloc(sizeof(t_spr));
    t_pos       *pos = malloc(sizeof(t_pos));

	if (ac < 2)
		return (-1);

    idx->big = big;
    idx->img = img;
    idx->parse = parse;
    idx->el = el;
    idx->window = window;
    idx->tex = tex;
    idx->spr = spr;
    idx->pos = pos;

    create_init(idx);
	if (parse_cub(idx, av[1]) < 0)
        return (-1);
    if (!(idx->window->mlx_ptr = mlx_init()))
        return (-1);
    idx->window->mlx_win = mlx_new_window(idx->window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y, WINDOW_TITLE);
    create_data(idx);
    idx->img->img = mlx_new_image(idx->window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y);
    idx->img->addr = (int *)mlx_get_data_addr(idx->img->img, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    create_algo(idx);
    mlx_hook(idx->window->mlx_win, 2, 1L<<1, ft_key, idx);
    mlx_loop(idx->window->mlx_ptr);
    return (0);
}
