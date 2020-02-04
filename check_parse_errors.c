/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 14:31:44 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		check_dir_letter(t_index *idx)
{
	if (idx->parse->dir == 'N' || idx->parse->dir == 'S' ||
		idx->parse->dir == 'E' || idx->parse->dir == 'W')
		return (0);
	return (-1);
}

int 	check_numbers(t_index *idx)
{
	int i;

	i = 0;
	while (idx->parse->map_string_clean[i] != '\0')
	{
		if (idx->parse->map_string_clean[i] != '1' &&
				idx->parse->map_string_clean[i] != '2' &&
				idx->parse->map_string_clean[i] != '0' &&
				idx->parse->map_string_clean[i] != 'N' &&
				idx->parse->map_string_clean[i] != 'S' &&
				idx->parse->map_string_clean[i] != 'E' &&
				idx->parse->map_string_clean[i] != 'W' &&
				idx->parse->map_string_clean[i] != '\n')
			return (-1);
		i++;
	}
	return (0);
}

/*
** error for first column already checked in the parse_data_and_map function
*/

int		check_error(t_index *idx)
{
	int j;

	j = 0;
	while (idx->parse->map[0][j] != '\0')
	{
		if (idx->parse->map[0][j] != '1')
			return (-1);
		j++;
	}
	j = 0;
	while (idx->parse->map[idx->parse->line_nbr - 1][j] != '\0')
	{
		if (idx->parse->map[idx->parse->line_nbr - 1][j] != '1')
			return (-1);
		j++;
	}
	j = 0;
	while (j < idx->parse->line_nbr)
	{
		if (idx->parse->map[j][idx->parse->column_nbr - 1] != '1')
			return (-1);
		j++;
	}
	if (check_dir_letter(idx) < 0)
		return (-1);
	if (check_numbers(idx) < 0)
		return (-1);
	return (0);
}
