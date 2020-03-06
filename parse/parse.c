/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:15:48 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/06 15:04:47 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int parse_data(int fd, t_index *idx)
{
    char *line;
    int i;

    i = 0;
    idx->parse->data = "";
    while (get_next_line(fd, &line) && i < 7)
    {
        if (line[0] == '\0')
			get_next_line(fd, &line);
        if (!ft_isdigit(line[0]))
        {
			idx->parse->data = ft_strjoin(idx->parse->data, line);
			idx->parse->data = ft_strjoin(idx->parse->data, "\n");
			free(line);
			line = NULL;
            i++;
        }
    }
	while (line[0] == '\0')
		get_next_line(fd, &line);
	idx->parse->data = ft_strjoin(idx->parse->data, line);
	idx->parse->data = ft_strjoin(idx->parse->data, "\0");
	free(line);
	line = NULL;
    return (1);
}

int parse_map(int fd, t_index *idx)
{
    char *line;

	line = "";
    idx->parse->map_string = "";
	while (line[0] == '\0')
		get_next_line(fd, &line);
	idx->parse->map_string = ft_strjoin(idx->parse->map_string, line);
	idx->parse->map_string = ft_strjoin(idx->parse->map_string, "\n");
    while (get_next_line(fd, &line))
    {
        if (line[0] == '\0')
		{
            write(1, "Error\n", 6);
            write(1, "Map not surrounded by 1\n", 24);
            return (-1);
        }
        idx->parse->map_string = ft_strjoin(idx->parse->map_string, line);
        idx->parse->map_string = ft_strjoin(idx->parse->map_string, "\n");
        free(line);
        line = NULL;
    }
    idx->parse->map_string = ft_strjoin(idx->parse->map_string, line);
	idx->parse->map_string = ft_strjoin(idx->parse->map_string, "\0");
	free(line);
	line = NULL;
    return (1);
}

char *create_new_line(char *str, int diff)
{
    int i;
    char *new;

    i = 0;
    if (!(new = malloc(sizeof(char *) * (new_strlen(str) + diff + 1))))
        return (NULL);
    while (str[i] != '\0')
    {
        new[i] = str[i];
        i++;
    }
    while (diff > 0)
    {
        new[i] = ' ';
        i++;
        diff--;
    }
    new[i] = '\0';
    return (new);
}

int create_good_size_map(t_index *idx)
{
    int i;
	int j;
    int len;
    int diff;
    
    i = 0;
    j = 0;
    diff = 0;
    len = new_strlen(idx->parse->map[i]);
    while (idx->parse->map[i] != NULL)
	{
		if (new_strlen(idx->parse->map[i]) > len)
            len = new_strlen(idx->parse->map[i]);
		i++;
	}
    i = 0;
    while (idx->parse->map[i] != NULL)
	{
		if (new_strlen(idx->parse->map[i]) < len)
        {
            diff = len - new_strlen(idx->parse->map[i]);
            if (!(idx->parse->map[i] = create_new_line(idx->parse->map[i], diff)))
				return (-1);
        }
		i++;
	}
    return (1);
}

int create_map(t_index *idx)
{
    int i;
	int j;

    if (!(idx->parse->map = ft_strsplit(idx->parse->map_string, '\n')))
		return (-1);
    i = 0;
	j = 0;
	while (idx->parse->map[i] != NULL)
	{
		j = 0;
		while (idx->parse->map[i][j] != '\0')
		{
			if ((ft_isalpha(idx->parse->map[i][j])))
			{
				idx->parse->pos_x_init = j + 0.5;
				idx->parse->pos_y_init = i + 0.5;
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
	if (check_borders(idx) < 0)
		return (-1);
    if (create_good_size_map(idx) < 0)
        return (-1);
    return (1);
}

int malloc_size_sprite(t_index *idx)
{
	if (!(idx->spr->sprites_x = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
	{
        write (1, "Error\n", 6);
		write (1, "Can't malloc the sprite", 23);
		return (-1);
	}
    if (!(idx->spr->sprites_y = malloc(sizeof(int *) * idx->spr->numSprites + 1)))
    {
        write (1, "Error\n", 6);
		write (1, "Can't malloc the sprite", 23);
		return (-1);
	}
	return (1);
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
				idx->spr->sprites_x[k] = j + 0.5;
				idx->spr->sprites_y[k] = i + 0.5;
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
	
	fd = open(filename, O_RDONLY);
	if (parse_data(fd, idx) < 0)
		return (-1);
    if (parse_map(fd, idx) < 0)
        return (-1);
	close(fd);
	create_map(idx);
	malloc_size_sprite(idx);
	parse_sprites(idx);
	if (create_elements(idx) < 0)
		return (-1);
	if (check_elements_errors(idx) < 0)
		return (-1);
	if (check_map_errors(idx) < 0)
		return (-1);
	return (1);
}
