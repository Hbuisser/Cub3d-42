/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:15:48 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/29 17:18:05 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_data_and_map(int fd, t_index *idx)
{
	char 	*line;

	idx->parse->map_string = "";
	idx->parse->data = "";
	while (get_next_line(fd, &line))
	{
		if (line[0] == '\0')
			get_next_line(fd, &line);
		if (!ft_isdigit(line[0]))
		{
			idx->parse->data = ft_strjoin(idx->parse->data, line);
			idx->parse->data = ft_strjoin(idx->parse->data, "\n");
			free(line);
			line = NULL;
		}
		else
		{
			if (line[0] == '1')
			{
				idx->parse->map_string = ft_strjoin(idx->parse->map_string, line);
				idx->parse->map_string = ft_strjoin(idx->parse->map_string, "\n");
				free(line);
				line = NULL;
			}
			else
			{
				write(1, "Error\n", 6);
				write(1, "map not surrounded by 1", 23);
				return (-1);
			}
		}
	}
	idx->parse->map_string = ft_strjoin(idx->parse->map_string, line);
	idx->parse->map_string = ft_strjoin(idx->parse->map_string, "\0");
	idx->parse->data = ft_strjoin(idx->parse->data, "\0");
	free(line);
	line = NULL;
	return (0);
}

int count_no_spaces(t_index *idx)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (idx->parse->map_string[++i] != '\0')
		if (idx->parse->map_string[i] != ' ')
			count++;
	return (count);
}

char *create_map(t_index *idx, int count)
{
	int i;
	int j;
	char *map_string_clean;

	i = 0;
	j = 0;
	if (!(map_string_clean = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (idx->parse->map_string[i] != '\0')
	{
		if (idx->parse->map_string[i] != ' ')
		{
			map_string_clean[j] = idx->parse->map_string[i];
			j++;
		}
		i++;
	}
	map_string_clean[j] = '\0';
	if (!(idx->parse->map = ft_strsplit(map_string_clean, '\n')))
		return (NULL);
	i = 0;
	j = 0;
	while (idx->parse->map[i] != NULL)
	{
		j = 0;
		while (idx->parse->map[i][j] != '\0')
		{
			if ((ft_isalpha(idx->parse->map[i][j])))
			{
				idx->parse->pos_x_init = j;
				idx->parse->pos_y_init = i;
				idx->parse->dir = idx->parse->map[i][j];
				idx->parse->map[i][j] = '0';
			}
			if (idx->parse->map[i][j] == '2')
				idx->spr->numSprites += 1;
			j++;
		}
		i++;
	}
	idx->parse->line_nbr = i;
	idx->parse->column_nbr = j;
	return (map_string_clean);
}

int malloc_size_sprite(t_index *idx)
{
	if (!(idx->spr->sprites_x = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
	{
        write (1, "Error\n", 6);
		return (-1);
	}
    if (!(idx->spr->sprites_y = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
    {
        write (1, "Error\n", 6);
		return (-1);
	}
	if (!(idx->spr->spriteOrder = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
    {
        write (1, "Error\n", 6);
		return (-1);
	}
	if (!(idx->spr->spriteDistance = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
    {
        write (1, "Error\n", 6);
		return (-1);
	}
	return (0);
}

void parse_sprites(t_index *idx)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (idx->parse->map[i] != NULL)
	{
		j = 0;
		while (idx->parse->map[i][j] != '\0')
		{
			if (idx->parse->map[i][j] == '2')
			{
				if (idx->parse->map[i - 1][j] == '1' || idx->parse->map[i][j - 1] == '1')
				{
					idx->spr->sprites_x[k] = j + 1;
					idx->spr->sprites_y[k] = i + 1;
				}
				else
				{
					idx->spr->sprites_x[k] = j + 0.5;
					idx->spr->sprites_y[k] = i + 0.5;
				}
				k++;
			}
			j++;
		}
		i++;
	}
}

int parse_cub(t_index *idx, char *filename)
{
	int		fd;
	int 	count;
	char 	*map_string_clean;
	
	fd = open(filename, O_RDONLY);
	if (parse_data_and_map(fd, idx) < 0)
		return (-1);
	close(fd);
	count = count_no_spaces(idx);
	map_string_clean = create_map(idx, count);
	malloc_size_sprite(idx);
	parse_sprites(idx);
	if (create_elements(idx) < 0)
		return (-1);
	if (check_elements_errors(idx) < 0)
		return (-1);
	if (check_map_errors(idx, map_string_clean) < 0)
		return (-1);
	return (1);
}
