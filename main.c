/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/13 17:51:44 by hbuisser         ###   ########.fr       */
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

/*void sprites_raycasting(t_index *idx)
{
    int i;
    int y;
    
    i = 0;
    y = 0;
    while (i < numSprites)
    {
        //translate sprite position to relative to camera
        idx->spr->spriteX = sprite[spriteOrder[i]].x - idx->parse->posX;
        idx->spr->spriteY = sprite[spriteOrder[i]].y - idx->parse->posY;
        //transform sprite with the inverse camera matrix
        // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
        // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
        // [ planeY   dirY ]                                          [ -planeY  planeX ]

        //required for correct matrix multiplication
        idx->spr->invDet = 1.0 / (idx->big->planeX * idx->big->dirY - idx->big->dirX * idx->big->planeY);
        idx->spr->transformX = idx->spr->invDet * (idx->big->dirY * idx->spr->spriteX - idx->big->dirX * idx->spr->spriteY);
        //this is actually the depth inside the screen, that what Z is in 3D
        idx->spr->transformY = idx->spr->invDet * (-idx->big->planeY * idx->spr->spriteX + idx->big->planeX * idx->spr->spriteY);
        idx->spr->spriteScreenX = (int)((w / 2) * (1 + idx->spr->transformX / idx->spr->transformY));

        //parameters for scaling and moving the sprites
        idx->spr->vMoveScreen = (int)(vMove / idx->spr->transformY);

        //calculate height of the sprite on screen
        idx->spr->spriteHeight = abs(int(h / (idx->spr->transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        idx->spr->drawStartY = -idx->spr->sprHeight / 2 + h / 2 + idx->spr->vMoveScreen;
        if(idx->spr->drawStartY < 0) 
            idx->spr->drawStartY = 0;
        idx->spr->drawEndY = idx->spr->sprHeight / 2 + h / 2 + idx->spr->vMoveScreen;
        if(idx->spr->drawEndY >= h) 
            idx->spr->drawEndY = h - 1;

        //calculate width of the sprite
        idx->spr->sprWidth = abs( int (h / (idx->spr->transformY))) / uDiv;
        idx->spr->drawStartX = -idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
        if(idx->spr->drawStartX < 0) 
            idx->spr->drawStartX = 0;
        idx->spr->drawEndX = idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
        if(idx->spr->drawEndX >= w) 
            idx->spr->drawEndX = w - 1;

        //loop through every vertical stripe of the sprite on screen
        idx->spr->stripe = idx->spr->drawStartX;
        while (idx->spr->stripe < idx->spr->drawEndX)
        {
            idx->spr->texX = (int)(128 * (idx->spr->stripe - (-idx->spr->spriteWidth / 2 + idx->spr->spriteScreenX)) * idx->spr->texWidth / idx->spr->spriteWidth) / 128;
            //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            if(idx->spr->transformY > 0 && idx->spr->stripe > 0 && idx->spr->stripe < w && idx->spr->transformY < ZBuffer[idx->spr->stripe])
            {
                y = idx->spr->drawStartY;
                //for every pixel of the current stripe
                while (y < idx->spr->drawEndY)
                {
                    int d = (y - idx->spr->vMoveScreen) * 128 - h * 64 + idx->spr->sprHeight * 64; //256 and 128 factors to avoid floats
                    idx->spr->texY = ((d * idx->tex->texHeight) / idx->spr->sprHeight) / 128;
                    
                    Uint32 color = texture[sprite[spriteOrder[i]].texture][idx->tex->texWidth * idx->tex->texY + idx->tex->texX]; //get current color from the texture
                    if((color & 0x00FFFFFF) != 0) 
                        buffer[y][idx->spr->stripe] = color; //paint pixel if it isn't black, black is the invisible color
                    y++;
                }
            }
            idx->spr->stripe++
        }
        i++;
    }
    drawBuffer(buffer[0]);
    for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
}*/

/*void sortSprites(int* spriteOrder, double* spriteDistance, int numSprites)
{
    int i;

    i = 0;
    while (i < numSprites)
    {
        
        i++;
    }
}*/

void create_algo(t_index *idx)
{
    int		i;
    int		hit;
    float   ZBuffer[idx->el->resolution_x];
    //int     spriteOrder[numSprites];
    //float   spriteDistance[numSprites];

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
        ZBuffer[i] = idx->big->perpWallDist;
        verLine(i, idx);
        i++;
    }
    /*i = 0;
    while (i < numSprites)
    {
        spriteOrder[i] = i;
        spriteDistance[i] = ((idx->parse->posX - idx->spr->spr_tex.idx->el->resolution_x) * (idx->parse->posX - idx->spr->spr_tex.idx->el->resolution_x) +
                (idx->parse->posY - idx->spr->spr_tex.idx->el->resolution_y) * (idx->parse->posY - idx->spr->spr_tex.idx->el->resolution_y));
        i++;
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);*/
    //sprites_raycasting(idx);
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
    t_sprite    *spr = malloc(sizeof(t_sprite));

	if (ac < 2)
		return (-1);

    idx->big = big;
    idx->img = img;
    idx->parse = parse;
    idx->el = el;
    idx->window = window;
    idx->tex = tex;
    idx->spr = spr;

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
