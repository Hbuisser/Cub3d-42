/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/08 18:06:55 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_dir_letter(t_index *idx)
{
	if (idx->parse->dir == 'N' || idx->parse->dir == 'S' ||
		idx->parse->dir == 'E' || idx->parse->dir == 'W')
		return (0);
	return (-1);
}

int 	check_map_characters(char *map_string_clean)
{
	int i;

	i = 0;
	while (map_string_clean[i] != '\0')
	{
		if (map_string_clean[i] != '1' &&
				map_string_clean[i] != '2' &&
				map_string_clean[i] != '0' &&
				map_string_clean[i] != 'N' &&
				map_string_clean[i] != 'S' &&
				map_string_clean[i] != 'E' &&
				map_string_clean[i] != 'W' &&
				map_string_clean[i] != '\n')
		{
			write(1, "map countains wrong things", 26);
			return (-1);
		}
		i++;
	}
	return (0);
}

/*
** error for first column already checked in the parse_data_and_map function
*/

int		check_borders(t_index *idx)
{
	int j;

	j = 0;
	while (idx->parse->map[0][j] != '\0')
	{
		if (idx->parse->map[0][j] != '1')
		{
			write(1, "map not surrounded by 1", 23);
			return (-1);
		}
		j++;
	}
	j = 0;
	while (idx->parse->map[idx->parse->line_nbr - 1][j] != '\0')
	{
		if (idx->parse->map[idx->parse->line_nbr - 1][j] != '1')
		{
			write(1, "map not surrounded by 1", 23);
			return (-1);
		}
		j++;
	}
	j = 0;
	while (j < idx->parse->line_nbr)
	{
		if (idx->parse->map[j][idx->parse->column_nbr - 1] != '1')
		{
			write(1, "map not surrounded by 1", 23);
			return (-1);
		}
		j++;
	}
	return (0);
}

int		check_map_errors(t_index *idx, char *map_string_clean)
{
	if (check_borders(idx) < 0)
		return (-1);
	if (check_dir_letter(idx) < 0)
		return (-1);
	if (check_map_characters(map_string_clean) < 0)
		return (-1);
	return (0);
}
