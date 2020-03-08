/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:12:28 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 16:53:16 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_east_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.east_line][++i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.east_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.e_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.east_line][i] != '\0')
	{
		m->el.e_path[j] = m->el.elem[m->el.east_line][i];
		i++;
		j++;
	}
	m->el.e_path[j] = '\0';
	return ("");
}

char	*get_west_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.west_line][++i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.west_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.w_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.west_line][i] != '\0')
	{
		m->el.w_path[j] = m->el.elem[m->el.west_line][i];
		i++;
		j++;
	}
	m->el.w_path[j] = '\0';
	return ("");
}

char	*get_south_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.south_line][++i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.south_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.s_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.south_line][i] != '\0')
	{
		m->el.s_path[j] = m->el.elem[m->el.south_line][i];
		i++;
		j++;
	}
	m->el.s_path[j] = '\0';
	return ("");
}

char	*get_north_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.north_line][++i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.north_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.n_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.north_line][i] != '\0')
	{
		m->el.n_path[j] = m->el.elem[m->el.north_line][i];
		i++;
		j++;
	}
	m->el.n_path[j] = '\0';
	return ("");
}

char	*get_sprite_texture(t_index *m)
{
	int	i;
	int	j;
	int	count;

	i = 2;
	count = 0;
	while (m->el.elem[m->el.sprite_line][i] == ' ')
		i++;
	j = i;
	i = i - 1;
	while (m->el.elem[m->el.sprite_line][i++] != '\0')
		count++;
	i = j;
	j = 0;
	if (!(m->el.spr_path = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (m->el.elem[m->el.sprite_line][i] != '\0')
	{
		m->el.spr_path[j] = m->el.elem[m->el.sprite_line][i];
		i++;
		j++;
	}
	m->el.spr_path[j] = '\0';
	return ("");
}
