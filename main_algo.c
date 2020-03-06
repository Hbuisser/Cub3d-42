/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:38:07 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/06 16:38:16 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculate_height_wall(t_index *idx)
{
    idx->big->wallHeight = idx->el->resolution_y * 0.5;
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
    if (idx->big->perpWallDist == 0)
        idx->big->perpWallDist = 0.1;
}

void perform_dda(int hit, t_index *idx)
{
    while (hit == 0)
    {
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
        if (idx->parse->map[idx->big->mapY][idx->big->mapX] == '1') 
            hit = 1;
    }
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
    idx->big->cameraX = 2 * i / (float)idx->el->resolution_x - 1;
    idx->big->rayDirX = idx->big->dirX + idx->big->planeX * idx->big->cameraX;
    idx->big->rayDirY = idx->big->dirY + idx->big->planeY * idx->big->cameraX;
    // mapX and mapY represent the current square of the map the ray is in
    idx->big->mapX = (int)idx->big->posX;
    idx->big->mapY = (int)idx->big->posY;
    // deltaDistX is the distance the ray has to travel to go from 1 x-side to the next x-side
    idx->big->deltaDistX = fabs(1 / idx->big->rayDirX);
    idx->big->deltaDistY = fabs(1 / idx->big->rayDirY);
}
