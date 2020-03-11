/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:32:55 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/11 15:12:25 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_paths(t_index *m)
{
	if (m->el.n_path)
	{
		free(m->el.n_path);
		m->el.n_path = 0;
	}
	if (m->el.s_path)
	{
		free(m->el.s_path);
		m->el.s_path = 0;
	}
	if (m->el.e_path)
	{
		free(m->el.e_path);
		m->el.e_path = 0;
	}
	if (m->el.w_path)
	{
		free(m->el.w_path);
		m->el.w_path = 0;
	}
}

void	free_elem(t_index *m)
{
	int i;

	i = -1;
	if (m->el.elem)
	{
		while (++i < 8)
		{
			free(m->el.elem[i]);
			m->el.elem[i] = 0;
		}
		free(m->el.elem);
		m->el.elem = 0;
	}
	free_paths(m);
	if (m->el.spr_path)
	{
		free(m->el.spr_path);
		m->el.spr_path = 0;
	}
}

void	free_map(t_index *m)
{
	int i;

	i = -1;
	if (m->parse.map)
	{
		while (++i < m->parse.line_nbr)
		{
			free(m->parse.map[i]);
			m->parse.map[i] = 0;
		}
		free(m->parse.map);
		m->parse.map = 0;
	}
	free(m->parse.map_string);
	m->parse.map_string = 0;
}

void	free_win(t_index *m)
{
	if (m->win.mlx_ptr && m->win.mlx_win)
		mlx_destroy_window(m->win.mlx_ptr, m->win.mlx_win);
}

int		exit_all(t_index *m)
{
	free_win(m);
	free_map(m);
	free_elem(m);
	free_tex(m);
	free_spr(m);
	exit(0);
	return (-1);
}
