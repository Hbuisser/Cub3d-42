/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:38:07 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 13:15:26 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_height_wall(t_index *m)
{
	m->big.wallHeight = m->el.res_y * 0.5;
	m->big.lineHeight = (int)(m->big.wallHeight / m->big.perpWallDist);
	m->big.drawStart = -m->big.lineHeight / 2 + m->el.res_y / 2;
	if (m->big.drawStart < 0)
		m->big.drawStart = 0;
	m->big.drawEnd = m->big.lineHeight / 2 + m->el.res_y / 2;
	if (m->big.drawEnd >= m->el.res_y)
		m->big.drawEnd = m->el.res_y - 1;
}

void	calculate_dist(t_index *m)
{
	if (m->big.side == 0)
		m->big.perpWallDist = (m->big.mapX - m->big.posX +
		(1 - m->big.stepX) / 2) / m->big.rayDirX;
	else
		m->big.perpWallDist = (m->big.mapY - m->big.posY +
		(1 - m->big.stepY) / 2) / m->big.rayDirY;
	if (m->big.perpWallDist == 0)
		m->big.perpWallDist = 0.1;
}

void	perform_dda(int hit, t_index *m)
{
	while (hit == 0)
	{
		if (m->big.sideDistX < m->big.sideDistY)
		{
			m->big.sideDistX += m->big.deltaDistX;
			m->big.mapX += m->big.stepX;
			m->big.side = 0;
		}
		else
		{
			m->big.sideDistY += m->big.deltaDistY;
			m->big.mapY += m->big.stepY;
			m->big.side = 1;
		}
		if (m->parse.map[m->big.mapY][m->big.mapX] == '1')
			hit = 1;
	}
}

void	calculate_step_and_sidedist(t_index *m)
{
	if (m->big.rayDirX < 0)
	{
		m->big.stepX = -1;
		m->big.sideDistX = (m->big.posX - m->big.mapX) * m->big.deltaDistX;
	}
	else
	{
		m->big.stepX = 1;
		m->big.sideDistX = (m->big.mapX + 1.0 - m->big.posX)
			* m->big.deltaDistX;
	}
	if (m->big.rayDirY < 0)
	{
		m->big.stepY = -1;
		m->big.sideDistY = (m->big.posY - m->big.mapY)
			* m->big.deltaDistY;
	}
	else
	{
		m->big.stepY = 1;
		m->big.sideDistY = (m->big.mapY + 1.0 - m->big.posY)
			* m->big.deltaDistY;
	}
}

/*
** mapX and mapY represent the current square of the map the ray is in
** deltaDistX : distance the ray has to travel from 1 x-side to next x-side
*/

void	calculate_ray_and_deltadist(int i, t_index *m)
{
	m->big.cameraX = 2 * i / (float)m->el.res_x - 1;
	m->big.rayDirX = m->big.dirX + m->big.planeX * m->big.cameraX;
	m->big.rayDirY = m->big.dirY + m->big.planeY * m->big.cameraX;
	m->big.mapX = (int)m->big.posX;
	m->big.mapY = (int)m->big.posY;
	m->big.deltaDistX = fabs(1 / m->big.rayDirX);
	m->big.deltaDistY = fabs(1 / m->big.rayDirY);
}
