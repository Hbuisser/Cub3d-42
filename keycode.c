/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 12:17:54 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key(int keycode, t_index *m)
{
    m->big.oldPlaneX = m->big.planeX;

    if (keycode == MLXK_ESC || keycode == MLXK_X)
        free_all(m, -1);
    else if (keycode == MLXK_W || keycode == MLXK_UP)
    {
        if (m->parse.map[(int)m->big.posY][(int)(m->big.posX + m->big.dirX * (m->big.moveSpeed + 0.1))] != '1')
            m->big.posX += m->big.dirX * m->big.moveSpeed;
        if (m->parse.map[(int)(m->big.posY + m->big.dirY * (m->big.moveSpeed + 0.1))][(int)m->big.posX] != '1')
            m->big.posY += m->big.dirY * m->big.moveSpeed;
    }
    else if (keycode == MLXK_S || keycode == MLXK_DOWN)
    {
        if (m->parse.map[(int)m->big.posY][(int)(m->big.posX - m->big.dirX * (m->big.moveSpeed * 0.1))] != '1')
            m->big.posX -= m->big.dirX * m->big.moveSpeed;
        if (m->parse.map[(int)(m->big.posY - m->big.dirY * (m->big.moveSpeed * 0.1))][(int)m->big.posX] != '1')
            m->big.posY -= m->big.dirY * m->big.moveSpeed;
    }

    if (keycode == MLXK_LEFT)
	{
        //if (m->parse.map[(int)(m->big.posY - m->big.dirX  * (m->big.moveSpeed + 0.1))][(int)m->big.posX] != '1')
			m->big.posY -= m->big.dirX * m->big.moveSpeed;
        //if (m->parse.map[(int)m->big.posX][(int)(m->big.posX + m->big.dirY * (m->big.moveSpeed + 0.1))] != '1')
			m->big.posX += m->big.dirY * m->big.moveSpeed;
	}
	if (keycode == MLXK_RIGHT)
	{
        //if (m->parse.map[(int)(m->big.posY + m->big.dirX * (m->big.moveSpeed * 0.1))][(int)m->big.posY] != '1')
			m->big.posY += m->big.dirX * m->big.moveSpeed;
        //if (m->parse.map[(int)m->big.posX][(int)(m->big.posX - m->big.dirY * (m->big.moveSpeed * 0.1))] != '1')
			m->big.posX -= m->big.dirY * m->big.moveSpeed;
	}
    
    else if (keycode == MLXK_D)
    {
        m->big.oldDirX = m->big.dirX;
        m->big.dirX = m->big.dirX * cos(m->big.rotSpeed) - m->big.dirY * sin(m->big.rotSpeed);
        m->big.dirY = m->big.oldDirX * sin(m->big.rotSpeed) + m->big.dirY * cos(m->big.rotSpeed);
        m->big.oldPlaneX = m->big.planeX;
        m->big.planeX = m->big.planeX * cos(m->big.rotSpeed) - m->big.planeY * sin(m->big.rotSpeed);
        m->big.planeY = m->big.oldPlaneX * sin(m->big.rotSpeed) + m->big.planeY * cos(m->big.rotSpeed);
    }
    else if (keycode == MLXK_A)
    {
        m->big.oldDirX = m->big.dirX;
        m->big.dirX = m->big.dirX * cos(-m->big.rotSpeed) - m->big.dirY * sin(-m->big.rotSpeed);
        m->big.dirY = m->big.oldDirX * sin(-m->big.rotSpeed) + m->big.dirY * cos(-m->big.rotSpeed);
        m->big.oldPlaneX = m->big.planeX;
        m->big.planeX = m->big.planeX * cos(-m->big.rotSpeed) - m->big.planeY * sin(-m->big.rotSpeed);
        m->big.planeY = m->big.oldPlaneX * sin(-m->big.rotSpeed) + m->big.planeY * cos(-m->big.rotSpeed);
    }
    mlx_clear_window(m->win.mlx_ptr, m->win.mlx_win);
    create_algo(m);
    return (0);
}

int exit_all(t_index *m)
{
    free_all(m, 1);
	exit(1);
    return (1);
}