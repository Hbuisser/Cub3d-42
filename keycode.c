/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:50:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 20:00:50 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		keys_up_down(t_index *m, int keycode)
{
	if (keycode == MLXK_W || keycode == MLXK_UP)
	{
		if (m->parse.map[(int)m->big.posy][(int)(m->big.posx +
		m->big.dirx * (m->big.movespeed + 0.1))] != '1')
			m->big.posx += m->big.dirx * m->big.movespeed;
		if (m->parse.map[(int)(m->big.posy + m->big.diry *
		(m->big.movespeed + 0.1))][(int)m->big.posx] != '1')
			m->big.posy += m->big.diry * m->big.movespeed;
	}
	if (keycode == MLXK_S || keycode == MLXK_DOWN)
	{
		if (m->parse.map[(int)m->big.posy][(int)(m->big.posx -
		m->big.dirx * (m->big.movespeed * 0.1))] != '1')
			m->big.posx -= m->big.dirx * m->big.movespeed;
		if (m->parse.map[(int)(m->big.posy - m->big.diry *
		(m->big.movespeed * 0.1))][(int)m->big.posx] != '1')
			m->big.posy -= m->big.diry * m->big.movespeed;
	}
	return (1);
}

int		keys_rot1(t_index *m, int keycode)
{
	if (keycode == MLXK_D)
	{
		m->big.olddirx = m->big.dirx;
		m->big.dirx = m->big.dirx * cos(m->big.rotspeed) -
			m->big.diry * sin(m->big.rotspeed);
		m->big.diry = m->big.olddirx * sin(m->big.rotspeed) +
			m->big.diry * cos(m->big.rotspeed);
		m->big.oldplanex = m->big.planex;
		m->big.planex = m->big.planex * cos(m->big.rotspeed) -
			m->big.planey * sin(m->big.rotspeed);
		m->big.planey = m->big.oldplanex * sin(m->big.rotspeed) +
			m->big.planey * cos(m->big.rotspeed);
	}
	return (1);
}

int		keys_rot2(t_index *m, int keycode)
{
	if (keycode == MLXK_A)
	{
		m->big.olddirx = m->big.dirx;
		m->big.dirx = m->big.dirx * cos(-m->big.rotspeed) -
			m->big.diry * sin(-m->big.rotspeed);
		m->big.diry = m->big.olddirx * sin(-m->big.rotspeed) +
			m->big.diry * cos(-m->big.rotspeed);
		m->big.oldplanex = m->big.planex;
		m->big.planex = m->big.planex * cos(-m->big.rotspeed) -
			m->big.planey * sin(-m->big.rotspeed);
		m->big.planey = m->big.oldplanex * sin(-m->big.rotspeed) +
			m->big.planey * cos(-m->big.rotspeed);
	}
	return (1);
}

int		keys_right_left(t_index *m, int keycode)
{
	if (keycode == MLXK_LEFT)
	{
		if (m->parse.map[(int)(m->big.posy - m->big.dirx *
		(m->big.movespeed + 0.1))][(int)m->big.posx] != '1')
			m->big.posy -= m->big.dirx * m->big.movespeed;
		if (m->parse.map[(int)m->big.posy][(int)(m->big.posx +
		m->big.diry * (m->big.movespeed + 0.1))] != '1')
			m->big.posx += m->big.diry * m->big.movespeed;
	}
	if (keycode == MLXK_RIGHT)
	{
		if (m->parse.map[(int)(m->big.posy + m->big.dirx *
		(m->big.movespeed * 0.1))][(int)m->big.posx] != '1')
			m->big.posy += m->big.dirx * m->big.movespeed;
		if (m->parse.map[(int)m->big.posy][(int)(m->big.posx -
		m->big.diry * (m->big.movespeed + 0.1))] != '1')
			m->big.posx -= m->big.diry * m->big.movespeed;
	}
	return (1);
}

int		ft_key(int keycode, t_index *m)
{
	m->big.oldplanex = m->big.planex;
	if (keycode == MLXK_ESC || keycode == MLXK_X)
		exit_all(m);
	keys_up_down(m, keycode);
	keys_rot1(m, keycode);
	keys_rot2(m, keycode);
	keys_right_left(m, keycode);
	mlx_clear_window(m->win.mlx_ptr, m->win.mlx_win);
	create_algo(m);
	return (0);
}
