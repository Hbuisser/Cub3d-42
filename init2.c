/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:56 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 17:18:41 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_e_w(t_index *m)
{
	if (m->parse.dir == 'E')
	{
		m->big.planeX = 0;
		m->big.planeY = 1.4;
		m->big.dirX = 1;
		m->big.dirY = 0;
	}
	if (m->parse.dir == 'W')
	{
		m->big.planeX = 0;
		m->big.planeY = -1.4;
		m->big.dirX = -1;
		m->big.dirY = 0;
	}
}

void	data_n_s(t_index *m)
{
	if (m->parse.dir == 'S')
	{
		m->big.planeX = -1.4;
		m->big.planeY = 0;
		m->big.dirX = 0;
		m->big.dirY = 1;
	}
	if (m->parse.dir == 'N')
	{
		m->big.planeX = 1.4;
		m->big.planeY = 0;
		m->big.dirX = 0;
		m->big.dirY = -1;
	}
}

int		create_data(t_index *m)
{
	data_e_w(m);
	data_n_s(m);
	m->big.posX = m->parse.pos_x_init;
	m->big.posY = m->parse.pos_y_init;
	m->tex.texWidth = 64;
	m->tex.texHeight = 64;
	m->spr.sprWidth = 0;
	m->spr.sprHeight = 0;
	m->big.moveSpeed = 0.2;
	m->big.rotSpeed = 0.04;
	if (!(m->spr.ZBuffer = malloc(sizeof(float *) * m->el.res_x + 1)))
		return (-1);
	return (1);
}

void	create_init(t_index *m)
{
	init_1(m);
	init_2(m);
	init_3(m);
	init_4(m);
	init_5(m);
}

int		exit_all(t_index *m)
{
	free_all(m, 1);
	exit(1);
	return (1);
}
