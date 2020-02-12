/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/11 15:49:53 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key(int keycode, t_index *idx)
{
    double moveSpeed;
    double oldDirX;
    double rotSpeed;
    double oldPlaneX;

    moveSpeed = 1;
    rotSpeed = 0.6;
    oldPlaneX = idx->big->planeX;

    if (keycode == MLXK_ESC || keycode == MLXK_X)
        exit(0);
    else if (keycode == MLXK_W || keycode == MLXK_UP)
    {
        // if 
        idx->big->posX += idx->big->dirX * moveSpeed;
        idx->big->posY += idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_S || keycode == MLXK_DOWN)
    {
        idx->big->posX -= idx->big->dirX * moveSpeed;
        idx->big->posY -= idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_A)
    {
        oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(rotSpeed) - idx->big->dirY * sin(rotSpeed);
        idx->big->dirY = oldDirX * sin(rotSpeed) + idx->big->dirY * cos(rotSpeed);
        oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(rotSpeed) - idx->big->planeY * sin(rotSpeed);
        idx->big->planeY = oldPlaneX * sin(rotSpeed) + idx->big->planeY * cos(rotSpeed);
    }
    else if (keycode == MLXK_D)
    {
        oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(-rotSpeed) - idx->big->dirY * sin(-rotSpeed);
        idx->big->dirY = oldDirX * sin(-rotSpeed) + idx->big->dirY * cos(-rotSpeed);
        oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(-rotSpeed) - idx->big->planeY * sin(-rotSpeed);
        idx->big->planeY = oldPlaneX * sin(-rotSpeed) + idx->big->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(idx->window->mlx_ptr, idx->window->mlx_win);
    create_algo(idx);
    return (0);
}
