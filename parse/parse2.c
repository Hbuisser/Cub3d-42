/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:58:21 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/09 15:54:35 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*create_new_line(char *str, int diff)
{
	int		i;
	char	*new;

	i = 0;
	if (!(new = malloc(sizeof(char *) * (new_strlen(str) + diff + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	while (diff > 0)
	{
		new[i] = ' ';
		i++;
		diff--;
	}
	new[i] = '\0';
	return (new);
}

int		create_good_size_map(t_index *m)
{
	int i;
	int len;
	int diff;

	i = 0;
	diff = 0;
	len = new_strlen(m->parse.map[i]);
	while (m->parse.map[i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) > len)
			len = new_strlen(m->parse.map[i]);
		i++;
	}
	i = 0;
	while (m->parse.map[i] != NULL)
	{
		if (new_strlen(m->parse.map[i]) < len)
		{
			diff = len - new_strlen(m->parse.map[i]);
			if (!(m->parse.map[i] = create_new_line(m->parse.map[i], diff)))
				return (-1);
		}
		i++;
	}
	return (1);
}

int		get_position2(t_index *m, int i, int j)
{
	if ((ft_isalpha(m->parse.map[i][j])))
	{
		m->parse.pos_x_init = j + 0.5;
		m->parse.pos_y_init = i + 0.5;
		if (m->parse.dir == 0)
			m->parse.dir = m->parse.map[i][j];
		else
			return (return_error(m));
		m->parse.map[i][j] = '0';
	}
	if (m->parse.map[i][j] == '2')
		m->spr.numsprites += 1;
	return (1);
}

int		get_position(t_index *m)
{
	int i;
	int j;

	i = 0;
	while (m->parse.map[i] != NULL)
	{
		j = 0;
		while (m->parse.map[i][j] != '\0')
		{
			get_position2(m, i, j);
			j++;
		}
		i++;
	}
	m->parse.line_nbr = i;
	m->parse.column_nbr = j;
	return (1);
}

int		create_map(t_index *m)
{
	if (!(m->parse.map = ft_strsplit(m->parse.map_string, '\n')))
		return (-1);
	if (get_position(m) < 0)
		return (-1);
	if (check_borders_lines(m) < 0)
		return (-1);
	if (check_borders_columns(m) < 0)
		return (-1);
	return (1);
}
