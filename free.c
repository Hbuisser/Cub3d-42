/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:32:55 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 12:18:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void free_spr(t_index *m)
{
    if (m->spr)
	{
		free(m->spr);
		m->spr = 0;
	}
}

void free_tex(t_index *m)
{
    if (m->tex)
	{
		free(m->tex);
    	m->tex = 0;
	}
}

void free_big(t_index *m)
{
	if (m->big)
	{
    	free(m->big);
    	m->big = 0;
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
}

void free_el(t_index *m)
{
    if (m->el)
	{
        free_elem(m);
		free(m->el);
    	m->el = 0;
	}
}

static void	free_map(t_index *m)
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
}

static void free_win(t_index *m)
{
    if (m->win.mlx_ptr && m->win.mlx_win)
	{
		mlx_destroy_window(m->win.mlx_ptr, m->win.mlx_win);
		free(m->win);
		m->win = 0;
	}
}

static void free_image(t_index *m)
{
    if (m->img)
		mlx_destroy_image(m->win.mlx_ptr, m->img);
}*/

int	free_all(t_index *m, int ret)
{
    /*free_image(m);
    free_win(m);
	free_map(m);
    free_el(m);
    free_big(m);
    free_tex(m);
    free_spr(m);*/
	m->parse.pos_x_init = 0;
	exit(0);
	return (ret);
}
