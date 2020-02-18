/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:18:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/17 22:01:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void sprites_raycasting(t_index *idx)
{
    int i;
    int y;
    int d;
    
    i = 0;
    y = 0;
    d = 0;
    while (i < idx->spr->numSprites)
    {
        idx->spr->spriteX = (float)idx->spr->x - (float)idx->big->posX;
        idx->spr->spriteY = (float)idx->spr->y - (float)idx->big->posY;
        idx->spr->invDet = 1.0 / (idx->big->planeX * idx->big->dirY - idx->big->dirX * idx->big->planeY);
        
        idx->spr->transformX = idx->spr->invDet * (idx->big->dirY * idx->spr->spriteX - idx->big->dirX * idx->spr->spriteY);
        idx->spr->transformY = idx->spr->invDet * (((-idx->big->planeY) * idx->spr->spriteX) + (idx->big->planeX * idx->spr->spriteY));
        
        idx->spr->spriteScreenX = (int)((idx->el->resolution_x / 2) * (1 + idx->spr->transformX / idx->spr->transformY));
        idx->spr->vMoveScreen = (int)(vMove / idx->spr->transformY);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
        idx->spr->sprHeight = fabs(idx->el->resolution_y / idx->spr->transformY) / vDiv;
        idx->spr->drawStartY = -idx->spr->sprHeight / 2 + idx->el->resolution_y / 2 + idx->spr->vMoveScreen;
        if (idx->spr->drawStartY < 0)
            idx->spr->drawStartY = 0;
        idx->spr->drawEndY = idx->spr->sprHeight / 2 + idx->el->resolution_y / 2 + idx->spr->vMoveScreen;
        if (idx->spr->drawEndY >= idx->el->resolution_y)
            idx->spr->drawEndY = idx->el->resolution_y - 1;

        idx->spr->sprWidth = fabs(idx->el->resolution_y / idx->spr->transformY) / uDiv;
        idx->spr->drawStartX = -idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
        if (idx->spr->drawStartX < 0)
            idx->spr->drawStartX = 0;
        idx->spr->drawEndX = idx->spr->sprWidth / 2 + idx->spr->spriteScreenX;
        if (idx->spr->drawEndX >= idx->el->resolution_x)
            idx->spr->drawEndX = idx->el->resolution_x - 1;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
        idx->spr->stripe = idx->spr->drawStartX;
        while (idx->spr->stripe < idx->spr->drawEndX)
        {
            idx->spr->texX = (int)((idx->spr->stripe - (-idx->spr->sprWidth / 2 + idx->spr->spriteScreenX)) * idx->tex->texWidth / idx->spr->sprWidth);
            if (idx->spr->transformY > 0 && idx->spr->stripe > 0 && idx->spr->stripe < idx->el->resolution_x && idx->spr->transformY < idx->spr->ZBuffer[idx->spr->stripe])
            {
                y = idx->spr->drawStartY;
                while (y < idx->spr->drawEndY && idx->spr->texY < 64 && idx->spr->texX < 64)
                {
                    d = (y - idx->spr->vMoveScreen) * 128 - idx->el->resolution_y * 64 + idx->spr->sprHeight * 64;
                    idx->spr->texY = ((d * idx->tex->texHeight) / idx->spr->sprHeight) / 128;
                    if ((idx->spr->color[idx->spr->sprHeight * idx->spr->texY + idx->spr->texX] & 0x00FFFFFF) != 0)
                        idx->img->addr[y * idx->el->resolution_x + idx->spr->stripe] = idx->spr->color[idx->spr->sprHeight * idx->spr->texY + idx->spr->texX];
                    y++;
                }
            }
            idx->spr->stripe++;
        }
        i++;
    }
    /*drawBuffer(buffer[0]);
    //clear the buffer instead of cls()*/
    //for(int y = 0; y < h; y++) 
      //  for(int x = 0; x < w; x++) 
        //    buffer[y][x] = 0;
}

/*void sortSprites(int* spriteOrder, float spriteDistance, t_index *idx)
{
    int i;

    i = 0;
    while (i < idx->spr->numSprites)
    {
        if (spriteDistance[i] > spriteDistance[i + 1])
        {
            spriteOrder[i] = spriteOrder[i + 1];
            spriteOrder[i + 1] = spriteOrder[i];
        }
        i++;
    }
    i = 0;
    while (i < 5)
    {
        printf("%d\n", spriteOrder[i]);
        i++;
    }
}*/