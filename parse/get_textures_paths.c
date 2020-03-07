/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:12:28 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 11:00:49 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char *get_east_texture(t_index *idx)
{
    int	i;
    int	j;
    int	count;

    i = 2;
    count = 0;
    while (idx->el.elem[idx->el.east_line][++i] == ' ')
		i++;
	j = i;
    while (idx->el.elem[idx->el.east_line][i] != '\0')
    {
        count++;
        i++;
    }
	i = j;
    j = 0;
    if (!(idx->el.e_path = malloc(sizeof(char) * count + 1)))
        return (NULL);
	while (idx->el.elem[idx->el.east_line][i] != '\0')
	{
		idx->el.e_path[j] = idx->el.elem[idx->el.east_line][i];
        i++;
        j++;
	}
    idx->el.e_path[j] = '\0';
    return ("");
}

char *get_west_texture(t_index *idx)
{
    int	i;
    int	j;
    int	count;

    i = 2;
    count = 0;
    while (idx->el.elem[idx->el.west_line][++i] == ' ')
		i++;
	j = i;
    while (idx->el.elem[idx->el.west_line][i] != '\0')
    {
        count++;
        i++;
    }
	i = j;
    j = 0;
    if (!(idx->el.w_path = malloc(sizeof(char) * count + 1)))
        return (NULL);
	while (idx->el.elem[idx->el.west_line][i] != '\0')
	{
		idx->el.w_path[j] = idx->el.elem[idx->el.west_line][i];
        i++;
        j++;
	}
    idx->el.w_path[j] = '\0';
    return ("");
}

char *get_south_texture(t_index *idx)
{
    int	i;
    int	j;
    int	count;

    i = 2;
    count = 0;
    while (idx->el.elem[idx->el.south_line][++i] == ' ')
		i++;
	j = i;
    while (idx->el.elem[idx->el.south_line][i] != '\0')
    {
        count++;
        i++;
    }
	i = j;
    j = 0;
    if (!(idx->el.s_path = malloc(sizeof(char) * count + 1)))
        return (NULL);
	while (idx->el.elem[idx->el.south_line][i] != '\0')
	{
		idx->el.s_path[j] = idx->el.elem[idx->el.south_line][i];
        i++;
        j++;
	}
    idx->el.s_path[j] = '\0';
    return ("");
}

char *get_north_texture(t_index *idx)
{
    int	i;
    int	j;
    int	count;

    i = 2;
    count = 0;
    while (idx->el.elem[idx->el.north_line][++i] == ' ')
		i++;
	j = i;
    while (idx->el.elem[idx->el.north_line][i] != '\0')
    {
        count++;
        i++;
    }
	i = j;
    j = 0;
    if (!(idx->el.n_path = malloc(sizeof(char) * count + 1)))
        return (NULL);
	while (idx->el.elem[idx->el.north_line][i] != '\0')
	{
		idx->el.n_path[j] = idx->el.elem[idx->el.north_line][i];
        i++;
        j++;
	}
    idx->el.n_path[j] = '\0';
    return ("");
}

char *get_sprite_texture(t_index *idx)
{
    int	i;
    int	j;
    int	count;

    i = 2;
    count = 0;
    while (idx->el.elem[idx->el.sprite_line][i] == ' ')
		i++;
	j = i;
    while (idx->el.elem[idx->el.sprite_line][i] != '\0')
    {
        count++;
        i++;
    }
	i = j;
    j = 0;
    if (!(idx->el.spr_path = malloc(sizeof(char) * count + 1)))
        return (NULL);
	while (idx->el.elem[idx->el.sprite_line][i] != '\0')
	{
		idx->el.spr_path[j] = idx->el.elem[idx->el.sprite_line][i];
        i++;
        j++;
	}
    idx->el.spr_path[j] = '\0';
    return ("");
}
