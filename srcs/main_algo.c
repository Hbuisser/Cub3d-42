/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:38:07 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/11 14:37:05 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_height_wall(t_index *m)
{
	m->big.wallheight = m->el.res_y;
	m->big.lineheight = (int)(m->big.wallheight / m->big.perpwalldist);
	m->big.drawstart = -m->big.lineheight / 2 + m->el.res_y / 2;
	if (m->big.drawstart < 0)
		m->big.drawstart = 0;
	m->big.drawend = m->big.lineheight / 2 + m->el.res_y / 2;
	if (m->big.drawend >= m->el.res_y)
		m->big.drawend = m->el.res_y - 1;
}

void	calculate_dist(t_index *m)
{
	if (m->big.side == 0)
		m->big.perpwalldist = (m->big.mapx - m->big.posx +
		(1 - m->big.stepx) / 2) / m->big.raydirx;
	else
		m->big.perpwalldist = (m->big.mapy - m->big.posy +
		(1 - m->big.stepy) / 2) / m->big.raydiry;
	if (m->big.perpwalldist == 0)
		m->big.perpwalldist = 0.1;
}

void	perform_dda(int hit, t_index *m)
{
	while (hit == 0)
	{
		if (m->big.sidedistx < m->big.sidedisty)
		{
			m->big.sidedistx += m->big.deltadistx;
			m->big.mapx += m->big.stepx;
			m->big.side = 0;
		}
		else
		{
			m->big.sidedisty += m->big.deltadisty;
			m->big.mapy += m->big.stepy;
			m->big.side = 1;
		}
		if (m->parse.map[m->big.mapy][m->big.mapx] == '1')
			hit = 1;
	}
}

void	calculate_step_and_sidedist(t_index *m)
{
	if (m->big.raydirx < 0)
	{
		m->big.stepx = -1;
		m->big.sidedistx = (m->big.posx - m->big.mapx) * m->big.deltadistx;
	}
	else
	{
		m->big.stepx = 1;
		m->big.sidedistx = (m->big.mapx + 1.0 - m->big.posx)
			* m->big.deltadistx;
	}
	if (m->big.raydiry < 0)
	{
		m->big.stepy = -1;
		m->big.sidedisty = (m->big.posy - m->big.mapy)
			* m->big.deltadisty;
	}
	else
	{
		m->big.stepy = 1;
		m->big.sidedisty = (m->big.mapy + 1.0 - m->big.posy)
			* m->big.deltadisty;
	}
}

void	calculate_ray_and_deltadist(int i, t_index *m)
{
	m->big.camerax = 2 * i / (float)m->el.res_x - 1;
	m->big.raydirx = m->big.dirx + m->big.planex * m->big.camerax;
	m->big.raydiry = m->big.diry + m->big.planey * m->big.camerax;
	m->big.mapx = (int)m->big.posx;
	m->big.mapy = (int)m->big.posy;
	m->big.deltadistx = fabs(1 / m->big.raydirx);
	m->big.deltadisty = fabs(1 / m->big.raydiry);
}
