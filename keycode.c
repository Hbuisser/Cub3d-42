/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/06 15:40:27 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key(int keycode, t_index *idx)
{
    idx->big->oldPlaneX = idx->big->planeX;

    if (keycode == MLXK_ESC || keycode == MLXK_X)
        free_all(idx, -1);
    else if (keycode == MLXK_W || keycode == MLXK_UP)
    {
        if (idx->parse->map[(int)idx->big->posY][(int)(idx->big->posX + idx->big->dirX * (idx->big->moveSpeed + 0.1))] != '1')
            idx->big->posX += idx->big->dirX * idx->big->moveSpeed;
        if (idx->parse->map[(int)(idx->big->posY + idx->big->dirY * (idx->big->moveSpeed + 0.1))][(int)idx->big->posX] != '1')
            idx->big->posY += idx->big->dirY * idx->big->moveSpeed;
    }
    else if (keycode == MLXK_S || keycode == MLXK_DOWN)
    {
        if (idx->parse->map[(int)idx->big->posY][(int)(idx->big->posX - idx->big->dirX * (idx->big->moveSpeed * 0.1))] != '1')
            idx->big->posX -= idx->big->dirX * idx->big->moveSpeed;
        if (idx->parse->map[(int)(idx->big->posY - idx->big->dirY * (idx->big->moveSpeed * 0.1))][(int)idx->big->posX] != '1')
            idx->big->posY -= idx->big->dirY * idx->big->moveSpeed;
    }
    if (keycode == MLXK_LEFT)
	{
        if (idx->parse->map[(int)idx->big->posY][(int)(idx->big->posX - idx->big->dirX * (idx->big->moveSpeed * 0.1))] != '1')
			idx->big->posY -= idx->big->dirX * idx->big->moveSpeed;
        if (idx->parse->map[(int)(idx->big->posY - idx->big->dirY * (idx->big->moveSpeed * 0.1))][(int)idx->big->posX] != '1')
			idx->big->posX += idx->big->dirY * idx->big->moveSpeed;
	}
	if (keycode == MLXK_RIGHT)
	{
        if (idx->parse->map[(int)idx->big->posY][(int)(idx->big->posX - idx->big->dirX * (idx->big->moveSpeed * 0.1))] != '1')
			idx->big->posY += idx->big->dirX * idx->big->moveSpeed;
        if (idx->parse->map[(int)(idx->big->posY - idx->big->dirY * (idx->big->moveSpeed * 0.1))][(int)idx->big->posX] != '1')
			idx->big->posX -= idx->big->dirY * idx->big->moveSpeed;
	}
    else if (keycode == MLXK_D)
    {
        idx->big->oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(idx->big->rotSpeed) - idx->big->dirY * sin(idx->big->rotSpeed);
        idx->big->dirY = idx->big->oldDirX * sin(idx->big->rotSpeed) + idx->big->dirY * cos(idx->big->rotSpeed);
        idx->big->oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(idx->big->rotSpeed) - idx->big->planeY * sin(idx->big->rotSpeed);
        idx->big->planeY = idx->big->oldPlaneX * sin(idx->big->rotSpeed) + idx->big->planeY * cos(idx->big->rotSpeed);
    }
    else if (keycode == MLXK_A)
    {
        idx->big->oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(-idx->big->rotSpeed) - idx->big->dirY * sin(-idx->big->rotSpeed);
        idx->big->dirY = idx->big->oldDirX * sin(-idx->big->rotSpeed) + idx->big->dirY * cos(-idx->big->rotSpeed);
        idx->big->oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(-idx->big->rotSpeed) - idx->big->planeY * sin(-idx->big->rotSpeed);
        idx->big->planeY = idx->big->oldPlaneX * sin(-idx->big->rotSpeed) + idx->big->planeY * cos(-idx->big->rotSpeed);
    }
    mlx_clear_window(idx->window->mlx_ptr, idx->window->mlx_win);
    create_algo(idx);
    return (0);
}

int exit_all(t_index *idx)
{
    free_all(idx, 1);
	exit(1);
    return (1);
}