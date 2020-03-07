/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:38:20 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 13:38:44 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_sprites(t_index *m)
{
	int y;
	int d;

	y = 0;
	d = 0;
	y = m->spr.drawStartY;
	while (y < m->spr.drawEndY)
	{
		d = (y) * 256 - m->el.res_y * 128 + m->spr.sprHeight * 128;
		m->spr.texY = ((d * 64) / m->spr.sprHeight) / 256;
		if ((m->spr.color[64 * m->spr.texY + m->spr.texX] & 0x00FFFFFF) != 0)
			m->img.addr[y * m->el.res_x + m->spr.stripe] =
				m->spr.color[64 * m->spr.texY + m->spr.texX];
		y++;
	}
}

void	verline_sprites(t_index *m)
{
	m->spr.stripe = m->spr.drawStartX;
	while (m->spr.stripe < m->spr.drawEndX)
	{
		m->spr.texX = (int)(m->spr.stripe - (-m->spr.sprWidth / 2
		+ m->spr.spriteScreenX)) * 64 / m->spr.sprWidth;
		if (m->spr.transformY > 0 && m->spr.stripe > 0 && m->spr.stripe <
			m->el.res_x && m->spr.transformY < m->spr.ZBuffer[m->spr.stripe]
				&& m->spr.texX < 64)
		{
			write_sprites(m);
		}
		m->spr.stripe++;
	}
}
