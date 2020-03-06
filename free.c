/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:32:55 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/06 16:11:31 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_spr(t_index *idx)
{
    if (idx->spr)
	{
		free(idx->spr);
		idx->spr = 0;
	}
}

void free_tex(t_index *idx)
{
    if (idx->tex)
	{
		free(idx->tex);
    	idx->tex = 0;
	}
}

void free_big(t_index *idx)
{
	if (idx->big)
	{
    	free(idx->big);
    	idx->big = 0;
	}
}

void	free_elem(t_index *idx)
{
	int i;

    i = -1;
	if (idx->el->elem)
	{
		while (++i < 8)
		{
			free(idx->el->elem[i]);
			idx->el->elem[i] = 0;
		}
		free(idx->el->elem);
		idx->el->elem = 0;
	}
}

void free_el(t_index *idx)
{
    if (idx->el)
	{
        free_elem(idx);
		free(idx->el);
    	idx->el = 0;
	}
}

static void	free_map(t_index *idx)
{
	int i;

    i = -1;
	if (idx->parse->map)
	{
		while (++i < idx->parse->line_nbr)
		{
			free(idx->parse->map[i]);
			idx->parse->map[i] = 0;
		}
		free(idx->parse->map);
		idx->parse->map = 0;
	}
}

static void free_window(t_index *idx)
{
    if (idx->window->mlx_ptr && idx->window->mlx_win)
	{
		mlx_destroy_window(idx->window->mlx_ptr, idx->window->mlx_win);
		free(idx->window);
		idx->window = 0;
	}
}

static void free_image(t_index *idx)
{
    if (idx->img)
		mlx_destroy_image(idx->window->mlx_ptr, idx->img);
}

int	free_all(t_index *idx, int ret)
{
    free_image(idx);
    free_window(idx);
	free_map(idx);
    free_el(idx);
    free_big(idx);
    free_tex(idx);
    free_spr(idx);
	exit(0);
	return (ret);
}
