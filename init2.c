/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:56 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 17:35:03 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_e_w(t_index *m)
{
	if (m->parse.dir == 'E')
	{
		m->big.planex = 0;
		m->big.planey = 1.4;
		m->big.dirx = 1;
		m->big.diry = 0;
	}
	if (m->parse.dir == 'W')
	{
		m->big.planex = 0;
		m->big.planey = -1.4;
		m->big.dirx = -1;
		m->big.diry = 0;
	}
}

void	data_n_s(t_index *m)
{
	if (m->parse.dir == 'S')
	{
		m->big.planex = -1.4;
		m->big.planey = 0;
		m->big.dirx = 0;
		m->big.diry = 1;
	}
	if (m->parse.dir == 'N')
	{
		m->big.planex = 1.4;
		m->big.planey = 0;
		m->big.dirx = 0;
		m->big.diry = -1;
	}
}

int		create_data(t_index *m)
{
	data_e_w(m);
	data_n_s(m);
	m->big.posx = m->parse.pos_x_init;
	m->big.posy = m->parse.pos_y_init;
	m->tex.texwidth = 64;
	m->tex.texheight = 64;
	m->spr.sprwidth = 0;
	m->spr.sprheight = 0;
	m->big.movespeed = 0.2;
	m->big.rotspeed = 0.04;
	if (!(m->spr.zbuffer = malloc(sizeof(float *) * m->el.res_x + 1)))
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
