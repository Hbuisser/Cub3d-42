/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:27:23 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/11 15:28:41 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_west_and_east(t_index *m)
{
	if (m->el.elem[m->el.west_line][0] != 'W' ||
		m->el.elem[m->el.west_line][1] != 'E')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong west texture path\n", 24);
		return (exit_all(m));
	}
	if (m->el.elem[m->el.east_line][0] != 'E' ||
		m->el.elem[m->el.east_line][1] != 'A')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong east texture path\n", 24);
		return (exit_all(m));
	}
	return (1);
}

int	check_north_and_south(t_index *m)
{
	if (m->el.elem[m->el.north_line][0] != 'N' ||
		m->el.elem[m->el.north_line][1] != 'O')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong north texture path\n", 25);
		return (exit_all(m));
	}
	if (m->el.elem[m->el.south_line][0] != 'S' ||
		m->el.elem[m->el.south_line][1] != 'O')
	{
		write(1, "Error\n", 6);
		write(1, "Wrong south texture path\n", 25);
		return (exit_all(m));
	}
	return (1);
}

int	check_path(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			write(1, "Error\n", 6);
			write(1, "Wrong texture path\n", 19);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	check_resolution(t_index *m)
{
	if (m->el.elem[m->el.resolution_line][0] != 'R')
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong resolution letter\n", 28);
		return (exit_all(m));
	}
	if (m->el.elem[m->el.resolution_line][1] != ' ' &&
		!ft_isdigit(m->el.elem[m->el.resolution_line][1]))
	{
		write(1, "Error\n", 6);
		write(1, "--> Wrong resolution details\n", 28);
		return (exit_all(m));
	}
	if (m->el.res_x > 2560)
		m->el.res_x = 2560;
	if (m->el.res_y > 1440)
		m->el.res_y = 1440;
	return (1);
}

int	check_elements_errors(t_index *m)
{
	if (check_north_and_south(m) < 0)
		return (-1);
	if (check_west_and_east(m) < 0)
		return (-1);
	if (check_path(m->el.n_path) < 0)
		return (-1);
	if (check_path(m->el.s_path) < 0)
		return (-1);
	if (check_path(m->el.w_path) < 0)
		return (-1);
	if (check_path(m->el.e_path) < 0)
		return (-1);
	if (check_path(m->el.spr_path) < 0)
		return (-1);
	if (check_resolution(m) < 0)
		return (-1);
	return (1);
}
