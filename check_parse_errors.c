/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 14:20:25 by hbuisser         ###   ########.fr       */
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
	return (0);
}
