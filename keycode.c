/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/01 16:25:57 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_key(int keycode, t_index *idx)
{
    idx->big->oldPlaneX = idx->big->planeX;

    if (keycode == MLXK_ESC || keycode == MLXK_X)
    {
        mlx_destroy_window(idx->window->mlx_ptr, idx->window->mlx_win);
        exit(0);
    }
    else if (keycode == MLXK_W || keycode == MLXK_UP)
    {
        //if (idx->parse->map[(int)(idx->big->posX + idx->big->dirX * idx->big->moveSpeed)][(int)idx->big->posY] != '1')
            idx->big->posX += idx->big->dirX * idx->big->moveSpeed;
        //if (idx->parse->map[(int)idx->big->posX][(int)(idx->big->posY + idx->big->dirY * idx->big->moveSpeed)] != '1')
            idx->big->posY += idx->big->dirY * idx->big->moveSpeed;
    }
    else if (keycode == MLXK_S || keycode == MLXK_DOWN)
    {
        //if (idx->parse->map[(int)(idx->big->posX - idx->big->dirX * idx->big->moveSpeed)][(int)idx->big->posY] != '1')
            idx->big->posX -= idx->big->dirX * idx->big->moveSpeed;
        //if (idx->parse->map[(int)idx->big->posX][(int)(idx->big->posY - idx->big->dirY * idx->big->moveSpeed)] != '1')
            idx->big->posY -= idx->big->dirY * idx->big->moveSpeed;
    }
    /*if (keycode == MLXK_TD)
	{
			idx->big->posY -= idx->big->dirX * moveSpeed;
			idx->big->posX += idx->big->dirY * moveSpeed;
	}
	if (keycode == MLXK_TG)
	{
			idx->big->posY += idx->big->dirX * moveSpeed;
			idx->big->posX -= idx->big->dirY * moveSpeed;
	}*/
    else if (keycode == MLXK_D || keycode == MLXK_RIGHT)
    {
        idx->big->oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(idx->big->rotSpeed) - idx->big->dirY * sin(idx->big->rotSpeed);
        idx->big->dirY = idx->big->oldDirX * sin(idx->big->rotSpeed) + idx->big->dirY * cos(idx->big->rotSpeed);
        idx->big->oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(idx->big->rotSpeed) - idx->big->planeY * sin(idx->big->rotSpeed);
        idx->big->planeY = idx->big->oldPlaneX * sin(idx->big->rotSpeed) + idx->big->planeY * cos(idx->big->rotSpeed);
    }
    else if (keycode == MLXK_A || keycode == MLXK_LEFT)
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