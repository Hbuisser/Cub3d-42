/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:15:48 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 15:18:14 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
				return (-1);
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

	i = -1;
	j = -1;
	if (!(idx->parse->map_string_clean = malloc(sizeof(char) * count + 1)))
		return (NULL);
	while (idx->parse->map_string[++i] != '\0')
		if (idx->parse->map_string[i] != ' ')
			idx->parse->map_string_clean[++j] = idx->parse->map_string[i];
	idx->parse->map_string_clean[++j] = '\0';
	idx->parse->map = ft_split(idx->parse->map_string_clean, '\n');
	i = 0;
	j = 0;
	while (idx->parse->map[i] != NULL)
	{
		j = 0;
		while (idx->parse->map[i][j] != '\0')
		{
			if ((ft_isalpha(idx->parse->map[i][j])))
			{
				idx->big->posX = j;
				idx->big->posY = i;
				idx->parse->dir = idx->parse->map[i][j];
				idx->parse->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	idx->parse->line_nbr = i;
	idx->parse->column_nbr = j;
	return (NULL);
}

int parse_cub(t_index *idx, char *filename)
{
	int		fd;
	int 	i;
	int 	count;
	
	fd = open(filename, O_RDONLY);
	if (parse_data_and_map(fd, idx) < 0)
		return (-1);
	close(fd);
	count = count_no_spaces(idx);
	create_map(idx, count);
	create_elements(idx);
	if (check_errors(idx) < 0)
		return (-1);
	i = 0;
	/*while (i < 14)
	{
		printf("%s\n", *idx->parse->map);
		idx->parse->map++;
		i++;
	}*/
	return (1);
}
