/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:08:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/09 14:36:57 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_hex_color(t_index *m)
{
	m->el.c_color_hex = transform_to_hex(m->el.c_r,
		m->el.c_g, m->el.c_b);
	m->el.f_color_hex = transform_to_hex(m->el.f_r,
		m->el.f_g, m->el.f_b);
}

void	check_letters(t_index *m, int i, int j)
{
	if (m->el.elem[i][j] == 'R')
		m->el.resolution_line = i;
	if (m->el.elem[i][j] == 'N')
		m->el.north_line = i;
	if (m->el.elem[i][j] == 'S')
	{
		if (m->el.elem[i][j + 1] == 'O')
			m->el.south_line = i;
		else
			m->el.sprite_line = i;
	}
	if (m->el.elem[i][j] == 'W')
		m->el.west_line = i;
	if (m->el.elem[i][j] == 'E')
		m->el.east_line = i;
	if (m->el.elem[i][j] == 'F')
		m->el.f_l = i;
	if (m->el.elem[i][j] == 'C')
		m->el.c_l = i;
}

void	create_elements_lines(t_index *m)
{
	int i;
	int j;

	i = 0;
	while (m->el.elem[i] != NULL)
	{
		j = 0;
		while (m->el.elem[i][j] != '\0')
		{
			check_letters(m, i, j);
			j++;
		}
		i++;
	}
}

int		get_elements(t_index *m)
{
	m->el.elem = ft_strsplit(m->parse.data, '\n');
	create_elements_lines(m);
	if (get_resolution(m) < 0)
		return (-1);
	if (get_floor_color(m) < 0)
		return (-1);
	if (get_ceilling_color(m) < 0)
		return (-1);
	create_hex_color(m);
	if (!get_sprite_texture(m))
		return (-1);
	if (!get_north_texture(m))
		return (-1);
	if (!get_south_texture(m))
		return (-1);
	if (!get_west_texture(m))
		return (-1);
	if (!get_east_texture(m))
		return (-1);
	return (1);
}
