/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/18 18:07:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key(int keycode, t_index *idx)
{
    float moveSpeed;
    float oldDirX;
    float rotSpeed;
    float oldPlaneX;

    moveSpeed = 0.2;
    rotSpeed = 0.2;
    oldPlaneX = idx->big->planeX;

// && pos > 0 && pos < posmax (strlen d'une ligne)
    if (keycode == MLXK_ESC || keycode == MLXK_X)
        exit(0);
    else if (keycode == MLXK_W || keycode == MLXK_UP)
    {
        idx->big->posX += idx->big->dirX * moveSpeed;
        idx->big->posY += idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_S || keycode == MLXK_DOWN)
    {
        idx->big->posX -= idx->big->dirX * moveSpeed;
        idx->big->posY -= idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_D)
    {
        oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(rotSpeed) - idx->big->dirY * sin(rotSpeed);
        idx->big->dirY = oldDirX * sin(rotSpeed) + idx->big->dirY * cos(rotSpeed);
        oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(rotSpeed) - idx->big->planeY * sin(rotSpeed);
        idx->big->planeY = oldPlaneX * sin(rotSpeed) + idx->big->planeY * cos(rotSpeed);
    }
    else if (keycode == MLXK_A)
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
