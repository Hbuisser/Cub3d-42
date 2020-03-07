/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:18:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 12:28:01 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void verline_sprites(t_index *m)
{
    int y;
    int d;

    y = 0;
    d = 0;
    m->spr.stripe = m->spr.drawStartX;
    while (m->spr.stripe < m->spr.drawEndX)
    {
        m->spr.texX = (int)(m->spr.stripe - (-m->spr.sprWidth / 2 + m->spr.spriteScreenX)) * 64 / m->spr.sprWidth;
        if (m->spr.transformY > 0 && m->spr.stripe > 0 && m->spr.stripe < m->el.res_x && m->spr.transformY < m->spr.ZBuffer[m->spr.stripe] && m->spr.texX < 64)
        {
            y = m->spr.drawStartY;
            while (y < m->spr.drawEndY)
            {
                d = (y) * 256 - m->el.res_y * 128 + m->spr.sprHeight * 128;
                m->spr.texY = ((d * 64) / m->spr.sprHeight) / 256;
                if ((m->spr.color[64 * m->spr.texY + m->spr.texX] & 0x00FFFFFF) != 0)
                    m->img.addr[y * m->el.res_x + m->spr.stripe] = m->spr.color[64 * m->spr.texY + m->spr.texX];
                y++;
            }
        }
        m->spr.stripe++;
    }
}

void calculate_draw_start_end(t_index *m)
{
    m->spr.sprHeight = (int)fabs((float)m->el.res_y / m->spr.transformY) / 2;
    m->spr.drawStartY = -m->spr.sprHeight / 2 + m->el.res_y / 2;
    if (m->spr.drawStartY < 0)
        m->spr.drawStartY = 0;
    m->spr.drawEndY = m->spr.sprHeight / 2 + m->el.res_y / 2;
    if (m->spr.drawEndY >= m->el.res_y)
        m->spr.drawEndY = m->el.res_y - 1;
        
    m->spr.sprWidth = (int)fabs((float)m->el.res_y / m->spr.transformY) / 2;
    m->spr.drawStartX = -m->spr.sprWidth / 2 + m->spr.spriteScreenX;
    if (m->spr.drawStartX < 0)
        m->spr.drawStartX = 0;
    m->spr.drawEndX = m->spr.sprWidth / 2 + m->spr.spriteScreenX;
    if (m->spr.drawEndX >= m->el.res_x)
        m->spr.drawEndX = m->el.res_x - 1;
}

void calculate_transform(int i, t_index *m)
{
    m->spr.spriteX = m->spr.sprites_x[i] - m->big.posX;
    m->spr.spriteY = m->spr.sprites_y[i] - m->big.posY;
    m->spr.invDet = 1.0 / (m->big.planeX * m->big.dirY - m->big.dirX * m->big.planeY);
    m->spr.transformX = m->spr.invDet * (m->big.dirY * m->spr.spriteX - m->big.dirX * m->spr.spriteY);
    m->spr.transformY = m->spr.invDet * (-m->big.planeY * m->spr.spriteX + m->big.planeX * m->spr.spriteY);
    m->spr.spriteScreenX = (int)((m->el.res_x / 2) * (1 + m->spr.transformX / m->spr.transformY));
}

void sort_sprites(t_index *m)
{
    int     tmp_x;
    int     tmp_y;
    int     j;
    int     i;

    i = 0;
    while (i < m->spr.numSprites)
    {
        j = i + 1;
        m->spr.spriteDistance = ((m->big.posX - m->spr.sprites_x[i]) * (m->big.posX - m->spr.sprites_x[i]) +
                    (m->big.posY - m->spr.sprites_y[i]) * (m->big.posY - m->spr.sprites_y[i]));
        while (j < m->spr.numSprites)
        {
            if (((m->big.posX - m->spr.sprites_x[j]) * (m->big.posX - m->spr.sprites_x[j]) +
                    (m->big.posY - m->spr.sprites_y[j]) * (m->big.posY - m->spr.sprites_y[j])) > m->spr.spriteDistance)
            {
                m->spr.spriteDistance = ((m->big.posX - m->spr.sprites_x[j]) * (m->big.posX - m->spr.sprites_x[j]) +
                    (m->big.posY - m->spr.sprites_y[j]) * (m->big.posY - m->spr.sprites_y[j]));
                tmp_x = m->spr.sprites_x[i];
                tmp_y = m->spr.sprites_y[i];
                m->spr.sprites_x[i] = m->spr.sprites_x[i + 1];
                m->spr.sprites_y[i] = m->spr.sprites_y[i + 1];
                m->spr.sprites_x[i + 1] = tmp_x;
                m->spr.sprites_y[i + 1] = tmp_y;
            }
            j++;
        }
        i++;
    }
}

void sprites_raycasting(t_index *m)
{
    int i;
    
    i = 0;
    sort_sprites(m);
    while (i < m->spr.numSprites)
    {
        calculate_transform(i, m);
        calculate_draw_start_end(m);
        verline_sprites(m);
        i++;
    }
}
