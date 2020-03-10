/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:18:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/10 12:51:02 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_draw_start_end(t_index *m)
{
	m->spr.sprheight = (int)fabs((float)m->el.res_y / m->spr.transformy);
	m->spr.drawstarty = -m->spr.sprheight / 2 + m->el.res_y / 2;
	if (m->spr.drawstarty < 0)
		m->spr.drawstarty = 0;
	m->spr.drawendy = m->spr.sprheight / 2 + m->el.res_y / 2;
	if (m->spr.drawendy >= m->el.res_y)
		m->spr.drawendy = m->el.res_y - 1;
	m->spr.sprwidth = (int)fabs((float)m->el.res_y / m->spr.transformy);
	m->spr.drawstartx = -m->spr.sprwidth / 2 + m->spr.spritescreenx;
	if (m->spr.drawstartx < 0)
		m->spr.drawstartx = 0;
	m->spr.drawendx = m->spr.sprwidth / 2 + m->spr.spritescreenx;
	if (m->spr.drawendx >= m->el.res_x)
		m->spr.drawendx = m->el.res_x - 1;
}

void	calculate_transform(int i, t_index *m)
{
	m->spr.spritex = m->spr.sprites_x[i] - m->big.posx;
	m->spr.spritey = m->spr.sprites_y[i] - m->big.posy;
	m->spr.invdet = 1.0 / (m->big.planex * m->big.diry
		- m->big.dirx * m->big.planey);
	m->spr.transformx = m->spr.invdet * (m->big.diry *
		m->spr.spritex - m->big.dirx * m->spr.spritey);
	m->spr.transformy = m->spr.invdet * (-m->big.planey *
		m->spr.spritex + m->big.planex * m->spr.spritey);
	m->spr.spritescreenx = (int)((m->el.res_x / 2) *
		(1 + m->spr.transformx / m->spr.transformy));
}

void	tmp(t_index *m, int i, int j)
{
	int	tmp_x;
	int	tmp_y;

	m->spr.spritedistance = ((m->big.posx - m->spr.sprites_x[j]) *
		(m->big.posx - m->spr.sprites_x[j]) +
		(m->big.posy - m->spr.sprites_y[j]) *
		(m->big.posy - m->spr.sprites_y[j]));
	tmp_x = m->spr.sprites_x[i];
	tmp_y = m->spr.sprites_y[i];
	m->spr.sprites_x[i] = m->spr.sprites_x[i + 1];
	m->spr.sprites_y[i] = m->spr.sprites_y[i + 1];
	m->spr.sprites_x[i + 1] = tmp_x;
	m->spr.sprites_y[i + 1] = tmp_y;
}

void	sort_sprites(t_index *m)
{
	int	j;
	int	i;

	i = 0;
	while (i < m->spr.numsprites)
	{
		j = i + 1;
		m->spr.spritedistance = ((m->big.posx - m->spr.sprites_x[i]) *
			(m->big.posx - m->spr.sprites_x[i]) +
			(m->big.posy - m->spr.sprites_y[i]) *
			(m->big.posy - m->spr.sprites_y[i]));
		while (j < m->spr.numsprites)
		{
			if (((m->big.posx - m->spr.sprites_x[j]) *
				(m->big.posx - m->spr.sprites_x[j]) +
				(m->big.posy - m->spr.sprites_y[j]) *
				(m->big.posy - m->spr.sprites_y[j])) > m->spr.spritedistance)
			{
				tmp(m, i, j);
			}
			j++;
		}
		i++;
	}
}

void	sprites_raycasting(t_index *m)
{
	int i;

	i = 0;
	sort_sprites(m);
	while (i < m->spr.numsprites)
	{
		calculate_transform(i, m);
		calculate_draw_start_end(m);
		verline_sprites(m);
		i++;
	}
}
