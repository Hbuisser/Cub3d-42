/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/09 14:28:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_map_characters(t_index *m)
{
	int i;

	i = 0;
	while (m->parse.map_string[i] != '\0')
	{
		if (m->parse.map_string[i] != '1' &&
			m->parse.map_string[i] != '2' &&
			m->parse.map_string[i] != '0' &&
			m->parse.map_string[i] != 'N' &&
			m->parse.map_string[i] != 'S' &&
			m->parse.map_string[i] != 'E' &&
			m->parse.map_string[i] != 'W' &&
			m->parse.map_string[i] != ' ' &&
			m->parse.map_string[i] != '\n')
		{
			write(1, "Error\n", 6);
			write(1, "Map countains wrong things\n", 27);
			return (-1);
		}
		i++;
	}
	return (1);
}

int		check_around2(int i, int j, t_index *m)
{
	if (m->parse.map[i - 1][j + 1] != ' ' &&
		m->parse.map[i - 1][j + 1] != '1' &&
		m->parse.map[i - 1][j + 1] != '\0')
		return (-1);
	if (m->parse.map[i - 1][j - 1] != ' ' &&
		m->parse.map[i - 1][j - 1] != '1' &&
		m->parse.map[i - 1][j - 1] != '\0')
		return (-1);
	if (m->parse.map[i + 1][j - 1] != ' ' &&
		m->parse.map[i + 1][j - 1] != '1' &&
		m->parse.map[i + 1][j - 1] != '\0')
		return (-1);
	if (m->parse.map[i + 1][j + 1] != ' ' &&
		m->parse.map[i + 1][j + 1] != '1' &&
		m->parse.map[i + 1][j + 1] != '\0')
		return (-1);
	return (1);
}

int		check_around1(int i, int j, t_index *m)
{
	if (m->parse.map[i][j - 1] != ' ' && m->parse.map[i][j - 1] != '1' &&
		m->parse.map[i][j - 1] != '\0')
		return (-1);
	if (m->parse.map[i][j + 1] != ' ' && m->parse.map[i][j + 1] != '1' &&
		m->parse.map[i][j + 1] != '\0')
		return (-1);
	if (m->parse.map[i - 1][j] != ' ' && m->parse.map[i - 1][j] != '1' &&
		m->parse.map[i - 1][j] != '\0')
		return (-1);
	if (m->parse.map[i + 1][j] != ' ' && m->parse.map[i + 1][j] != '1' &&
		m->parse.map[i + 1][j] != '\0')
		return (-1);
	return (1);
}

int		check_spaces_algo(t_index *m)
{
	int i;
	int j;

	i = 1;
	while (i < (m->parse.line_nbr - 1))
	{
		j = 1;
		while (m->parse.map[i][j] != '\0')
		{
			if ((m->parse.map[i][j] == ' ' && (check_around1(i, j, m) < 0)) ||
			(m->parse.map[i][j] == ' ' && (check_around2(i, j, m) < 0)))
			{
				write(1, "Error\n", 6);
				write(1, "Map not surrounded by 1\n", 24);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		check_map_errors(t_index *m)
{
	if (check_spaces_algo(m) < 0)
		return (-1);
	if (check_dir_letter(m) < 0)
		return (-1);
	if (check_map_characters(m) < 0)
		return (-1);
	return (1);
}
