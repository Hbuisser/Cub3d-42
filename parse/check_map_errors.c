/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 12:15:30 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	new_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int		check_dir_letter(t_index *m)
{
	if (m->parse.dir == 'N' || m->parse.dir == 'S' ||
		m->parse.dir == 'E' || m->parse.dir == 'W')
		return (0);
	return (-1);
}

int 	check_map_characters(t_index *m)
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
			write (1, "Error\n", 6);
			write (1, "Map countains wrong things\n", 27);
			return (-1);
		}
		i++;
	}
	return (1);
}

int		check_borders(t_index *m)
{
	int j;
    int i;

	j = 0;
	while (m->parse.map[0][j] != '\0')
	{
		if (m->parse.map[0][j] != '1' && m->parse.map[0][j] != ' ')
		{
			write(1, "Error\n", 6);
			write(1, "Map not surrounded by 1\n", 24);
			exit(0);
			return (-1);
		}
		j++;
	}
    j = 0;
	while (m->parse.map[m->parse.line_nbr - 1][j] != '\0')
	{
		if ((m->parse.map[m->parse.line_nbr - 1][j] != '1') && (m->parse.map[m->parse.line_nbr - 1][j] != ' '))
		{
			write(1, "Error\n", 6);
			write(1, "Map not surrounded by 1\n", 24);
			exit(0);
			return (-1);
		}
		j++;
	}
    i = 0;
	while (m->parse.map[i] != NULL)
	{
        j = 0;
        while (m->parse.map[i][j] != '\0')
            j++;
        if (m->parse.map[i][j - 1] != '1')
        {
            write(1, "Error\n", 6);
            write(1, "Map not surrounded by 1\n", 24);
            exit(0);
			return (-1);
        }
        i++;
	}
    i = 0;
    while (m->parse.map[i] != NULL)
	{
        if (m->parse.map[i][0] != '1' && m->parse.map[i][0] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "Map not surrounded by 1\n", 24);
            exit(0);
			return (-1);
        }
        i++;
	}
    return (1);
}

int check_around(int i, int j, t_index *m)
{
    if (m->parse.map[i][j - 1] != ' ' && m->parse.map[i][j - 1] != '1' && m->parse.map[i][j - 1] != '\0')
        return (-1);
    if (m->parse.map[i][j + 1] != ' ' && m->parse.map[i][j + 1] != '1' && m->parse.map[i][j + 1] != '\0')
        return (-1);
    if (m->parse.map[i - 1][j] != ' ' && m->parse.map[i - 1][j] != '1' && m->parse.map[i - 1][j] != '\0')
        return (-1);
    if (m->parse.map[i + 1][j] != ' ' && m->parse.map[i + 1][j] != '1' && m->parse.map[i + 1][j] != '\0')
        return (-1);
    if (m->parse.map[i - 1][j + 1] != ' ' && m->parse.map[i - 1][j + 1] != '1' && m->parse.map[i - 1][j + 1] != '\0')
        return (-1);
    if (m->parse.map[i - 1][j - 1] != ' ' && m->parse.map[i - 1][j - 1] != '1' && m->parse.map[i - 1][j - 1] != '\0')
        return (-1);
    if (m->parse.map[i + 1][j - 1] != ' ' && m->parse.map[i + 1][j - 1] != '1' && m->parse.map[i + 1][j - 1] != '\0')
        return (-1);
    if (m->parse.map[i + 1][j + 1] != ' ' && m->parse.map[i + 1][j + 1] != '1' && m->parse.map[i + 1][j + 1] != '\0')
        return (-1);
    return (1);
}

int check_spaces_algo(t_index *m)
{
	int i;
    int j;

	i = 1;
	while (i < (m->parse.line_nbr - 1))
	{
        j = 1;
		while (m->parse.map[i][j] != '\0')
        {
            if (m->parse.map[i][j] == ' ' && (check_around(i, j, m) < 0))
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
