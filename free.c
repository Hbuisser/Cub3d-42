/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:32:55 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/05 20:18:10 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void free_spr(t_index *idx)
{
    if (idx->spr)
	{
		free(idx->spr->spr_tex);
		idx->spr->spr_tex = 0;
        free(idx->spr->color);
		idx->spr->color = 0;
        free(idx->spr->ZBuffer);
		idx->spr->ZBuffer = 0;
        free(idx->spr->sprites_x);
		idx->spr->sprites_x = 0;
        free(idx->spr->sprites_y);
		idx->spr->sprites_y = 0;
	}
    free(idx->spr);
    idx->spr = 0;
}*/

/*void free_tex(t_index *idx)
{
    if (idx->tex)
	{
		free(idx->tex->color_n);
		idx->tex->color_n = 0;
        free(idx->tex->color_s);
		idx->tex->color_s = 0;
        free(idx->tex->color_w);
		idx->tex->color_w = 0;
        free(idx->tex->color_e);
		idx->tex->color_e = 0;
        free(idx->tex->color);
		idx->tex->color = 0;
	}
    free(idx->tex);
    idx->tex = 0;
}*/

/*void free_big(t_index *idx)
{
    free(idx->big);
    idx->big = 0;
}*/

/*void	free_elem(t_index *idx)
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
}*/

/*void free_el(t_index *idx)
{
    if (idx->el)
	{
		free(idx->el->n_path);
		idx->el->n_path = 0;
        free(idx->el->s_path);
		idx->el->s_path = 0;
        free(idx->el->w_path);
		idx->el->w_path = 0;
        free(idx->el->e_path);
		idx->el->e_path = 0;
        free(idx->el->spr_path);
		idx->el->spr_path = 0;
        free_elem(idx);
	}
    free(idx->el);
    idx->el = 0;
}*/

/*static void	free_map(t_index *idx)
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
}*/

/*static void free_parse(t_index *idx)
{
    if (idx->parse)
	{
		free(idx->parse->data);
		idx->parse->data = 0;
        free(idx->parse->map_string);
		idx->parse->map_string = 0;
        free(idx->parse->map_string_clean);
		idx->parse->map_string_clean = 0;
        free_map(idx);
	}
    free(idx->parse);
    idx->parse = 0;
}*/

/*static void free_window(t_index *idx)
{
    if (idx->window->mlx_ptr && idx->window->mlx_win)
	{
		mlx_destroy_window(idx->window->mlx_ptr, idx->window->mlx_win);
		free(idx->window);
		idx->window = 0;
	}
}*/

/*static void free_image(t_index *idx)
{
    if (idx->img)
	{
		mlx_destroy_image(idx->window->mlx_ptr, idx->img);
		free(idx->img);
		idx->img = 0;
	}
}*/

int			free_all(t_index *idx, int ret)
{
    //free_image(idx);
    //free_window(idx);
	//free_parse(idx);
    //free_el(idx);
    //free_big(idx);
    //free_tex(idx);
    free_spr(idx);
	idx->parse->line_nbr = 0;
	exit(0);
	return (ret);
}
