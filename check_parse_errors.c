/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 13:55:13 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	j = 0;
	// attention au parsing qui repere si c'est 1 ou pas plus tot dans le code
	while (j < idx->parse->line_nbr)
	{
		if (idx->parse->map[j][0] != '1')
			return (-1);
		j++;
	}
	return (0);
}
