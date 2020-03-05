/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:53:31 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/05 17:52:30 by hbuisser         ###   ########.fr       */
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

int		check_dir_letter(t_index *idx)
{
	if (idx->parse->dir == 'N' || idx->parse->dir == 'S' ||
		idx->parse->dir == 'E' || idx->parse->dir == 'W')
		return (0);
	return (-1);
}

int 	check_map_characters(t_index *idx)
{
	int i;

	i = 0;
	while (idx->parse->map_string[i] != '\0')
	{
		if (idx->parse->map_string[i] != '1' &&
				idx->parse->map_string[i] != '2' &&
				idx->parse->map_string[i] != '0' &&
				idx->parse->map_string[i] != 'N' &&
				idx->parse->map_string[i] != 'S' &&
				idx->parse->map_string[i] != 'E' &&
				idx->parse->map_string[i] != 'W' &&
				idx->parse->map_string[i] != ' ' &&
				idx->parse->map_string[i] != '\n')
		{
			write(1, "Error\n", 6);
			write (1, "Map countains wrong things", 26);
			return (-1);
		}
		i++;
	}
	return (1);
}

int		check_borders(t_index *idx)
{
	int j;
    int i;

	j = 0;
    // check first line
	while (idx->parse->map[0][j] != '\0')
	{
		if (idx->parse->map[0][j] != '1' && idx->parse->map[0][j] != ' ')
		{
			write(1, "Error\n", 6);
			write(1, "Map not surrounded by 1 one", 30);
			return (-1);
		}
		j++;
	}
    j = 0;
    // check last line
	while (idx->parse->map[idx->parse->line_nbr - 1][j] != '\0')
	{
		if ((idx->parse->map[idx->parse->line_nbr - 1][j] != '1') && (idx->parse->map[idx->parse->line_nbr - 1][j] != ' '))
		{
			write(1, "Error\n", 6);
			write(1, "Map not surrounded by 1 two", 30);
			return (-1);
		}
		j++;
	}
    i = 0;
    // check last column
	while (idx->parse->map[i] != NULL)
	{
        j = 0;
        while (idx->parse->map[i][j] != '\0')
            j++;
        if (idx->parse->map[i][j - 1] != '1')
        {
            write(1, "Error\n", 6);
            write(1, "Map not surrounded by 1 trhee", 30);
            return (-1);
        }
        i++;
	}
    // check first column
    i = 0;
    while (idx->parse->map[i] != NULL)
	{
        if (idx->parse->map[i][0] != '1' && idx->parse->map[i][0] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "Map not surrounded by 1 four", 30);
            return (-1);
        }
        i++;
	}
    return (1);
}

int check_around(int i, int j, t_index *idx)
{
    if (idx->parse->map[i][j - 1] != ' ' && idx->parse->map[i][j - 1] != '1' && idx->parse->map[i][j - 1] != '\0')
    {
        printf("1\n");
        printf("%s\n", idx->parse->map[i]);
        return (-1);
    }
    if (idx->parse->map[i][j + 1] != ' ' && idx->parse->map[i][j + 1] != '1' && idx->parse->map[i][j + 1] != '\0')
        return (-1);
    if (idx->parse->map[i - 1][j] != ' ' && idx->parse->map[i - 1][j] != '1' && idx->parse->map[i - 1][j] != '\0')
        return (-1);
    if (idx->parse->map[i + 1][j] != ' ' && idx->parse->map[i + 1][j] != '1' && idx->parse->map[i + 1][j] != '\0')
        return (-1);
    if (idx->parse->map[i - 1][j + 1] != ' ' && idx->parse->map[i - 1][j + 1] != '1' && idx->parse->map[i - 1][j + 1] != '\0')
        return (-1);
    if (idx->parse->map[i - 1][j - 1] != ' ' && idx->parse->map[i - 1][j - 1] != '1' && idx->parse->map[i - 1][j - 1] != '\0')
        return (-1);
    if (idx->parse->map[i + 1][j - 1] != ' ' && idx->parse->map[i + 1][j - 1] != '1' && idx->parse->map[i + 1][j - 1] != '\0')
        return (-1);
    if (idx->parse->map[i + 1][j + 1] != ' ' && idx->parse->map[i + 1][j + 1] != '1' && idx->parse->map[i + 1][j + 1] != '\0')
        return (-1);
    return (1);
}

int check_spaces_algo(t_index *idx)
{
	int i;
    int j;

    i = 1;
	while (i < (idx->parse->line_nbr - 2))
	{
        j = 1;
        while (idx->parse->map[i][j] != (idx->parse->map[i][new_strlen(idx->parse->map[i]) - 1]))
        {
            if (idx->parse->map[i][j] == ' ' && (check_around(i, j, idx) < 0))
            {
                write(1, "Error\n", 6);
                write(1, "Map not surrounded by 1", 23);
                return (-1);
            }
            j++;
        }
		i++;
	}
    return (1);
}

int		check_map_errors(t_index *idx)
{
	if (check_spaces_algo(idx) < 0)
		return (-1);
	if (check_dir_letter(idx) < 0)
		return (-1);
	if (check_map_characters(idx) < 0)
		return (-1);
	return (1);
}
