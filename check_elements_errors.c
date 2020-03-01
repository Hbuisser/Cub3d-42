/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:27:23 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/29 18:46:49 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_west_and_east(t_index *idx)
{
	if (idx->el->elem[idx->el->west_line][0] != 'W')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong first letter for the west texture path", 49);
		return (-1);
	}
	if (idx->el->elem[idx->el->west_line][1] != 'E')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong second letter for the west texture path", 50);
		return (-1);
	}
	if (idx->el->elem[idx->el->east_line][0] != 'E')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong first letter for the east texture path", 49);
		return (-1);
	}
	if (idx->el->elem[idx->el->east_line][1] != 'A')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong second letter for the east texture path", 50);
		return (-1);
	}
	return (0);
}

int	check_north_and_south(t_index *idx)
{
	if (idx->el->elem[idx->el->north_line][0] != 'N')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong first letter for the north texture path", 49);
		return (-1);
	}
	if (idx->el->elem[idx->el->north_line][1] != 'O')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong second letter for the north texture path", 50);
		return (-1);
	}
	if (idx->el->elem[idx->el->south_line][0] != 'S')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong first letter for the south texture path", 49);
		return (-1);
	}
	if (idx->el->elem[idx->el->south_line][1] != 'O')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong second letter for the south texture path", 50);
		return (-1);
	}
	return (0);
}

int check_path(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			write(1, "Error\n", 6);
			write(1, "--> Wrong path", 14);
			return (-1);
		}
		i++;
	}
	return (0);
}

int check_resolution(t_index *idx)
{
	if (idx->el->elem[idx->el->resolution_line][0] != 'R')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong resolution letter", 27);
		return (-1);
	}
	if (idx->el->elem[idx->el->resolution_line][1] != ' ' &&
			!ft_isdigit(idx->el->elem[idx->el->resolution_line][1]))
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong resolution details", 27);
		return (-1);
	}
	return (0);
}

int	check_elements_errors(t_index *idx)
{
	if (check_north_and_south(idx) < 0)
		return (-1);
    if (check_west_and_east(idx) < 0)
		return (-1);
	if (check_path(idx->el->n_path) < 0)
		return (-1);
	if (check_path(idx->el->s_path) < 0)
		return (-1);
	if (check_path(idx->el->w_path) < 0)
		return (-1);
	if (check_path(idx->el->e_path) < 0)
		return (-1);
	if (check_path(idx->el->spr_path) < 0)
		return (-1);
	if (check_resolution(idx) < 0)
		return (-1);
	return (0);
}
