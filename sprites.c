/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:18:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/06 13:59:24 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void verline_sprites(t_index *idx)
{
    int y;
    int d;

    y = 0;
    d = 0;
    idx->spr->stripe = idx->spr->drawStartX;
    while (idx->spr->stripe < idx->spr->drawEndX)
    {
        idx->spr->texX = (int)(128 * (idx->spr->stripe - (-idx->spr->sprWidth / 2 + idx->spr->spriteScreenX)) * idx->tex->texWidth / idx->spr->sprWidth) / 128;
        // check ici 
        if (idx->spr->transformY > 0 && idx->spr->stripe > 0 && idx->spr->stripe < idx->el->resolution_x && idx->spr->transformY < idx->spr->ZBuffer[idx->spr->stripe])
        {
            y = idx->spr->drawStartY;
            //while (y < idx->spr->drawEndY && idx->spr->texY < 64 && idx->spr->texX < 64)
            while (y < idx->spr->drawEndY)
            {
                d = (y - idx->spr->vMoveScreen) * 128 - idx->el->resolution_y * 64 + idx->spr->sprHeight * 64;
                idx->spr->texY = ((d * idx->tex->texHeight) / idx->spr->sprHeight) / 128;
                if ((idx->spr->color[64 * idx->spr->texY + idx->spr->texX] & 0x00FFFFFF) != 0)
                    idx->img->addr[y * idx->el->resolution_x + idx->spr->stripe] = idx->spr->color[64 * idx->spr->texY + idx->spr->texX];
                y++;
            }
        }
        idx->spr->stripe++;
    }
}

void calculate_draw_start_end(t_index *idx)
{
    idx->spr->sprHeight = (int)fabs(idx->el->resolution_y / idx->spr->transformY) / vDiv;
    idx->spr->drawStartY = -idx->spr->sprHeight / 2 + idx->el->resolution_y / 2 + idx->spr->vMoveScreen;
    if (idx->spr->drawStartY < 0)
        idx->spr->drawStartY = 0;
    idx->spr->drawEndY = idx->spr->sprHeight / 2 + idx->el->resolution_y / 2 + idx->spr->vMoveScreen;
    if (idx->spr->drawEndY >= idx->el->resolution_y)
        idx->spr->drawEndY = idx->el->resolution_y - 1;
        
    idx->spr->sprWidth = (int)fabs(idx->el->resolution_y / idx->spr->transformY) / uDiv;
    idx->spr->drawStartX = -idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
    if (idx->spr->drawStartX < 0)
        idx->spr->drawStartX = 0;
    idx->spr->drawEndX = idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
    if (idx->spr->drawEndX >= idx->el->resolution_x)
        idx->spr->drawEndX = idx->el->resolution_x - 1;
}

void calculate_transform(int i, t_index *idx)
{
    idx->spr->spriteX = (float)idx->spr->sprites_x[i] - (float)idx->big->posX;
    idx->spr->spriteY = (float)idx->spr->sprites_y[i] - (float)idx->big->posY;
    idx->spr->invDet = 1.0 / (idx->big->planeX * idx->big->dirY - idx->big->dirX * idx->big->planeY);
    
    idx->spr->transformX = idx->spr->invDet * (idx->big->dirY * idx->spr->spriteX - idx->big->dirX * idx->spr->spriteY);
    idx->spr->transformY = idx->spr->invDet * (-idx->big->planeY * idx->spr->spriteX + idx->big->planeX * idx->spr->spriteY);
    
    idx->spr->spriteScreenX = (int)((idx->el->resolution_x / 2) * (1 + idx->spr->transformX / idx->spr->transformY));
    idx->spr->vMoveScreen = (int)(vMove / idx->spr->transformY);
}

void sprites_raycasting(t_index *idx)
{
    int i;
    
    i = 0;
    while (i < idx->spr->numSprites)
    {
        calculate_transform(i, idx);
        calculate_draw_start_end(idx);
        verline_sprites(idx);
        i++;
    }
}
