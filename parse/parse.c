/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:15:48 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 16:59:08 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int write_error_one()
{
	write(1, "Error\n", 6);
	write(1, "Map not surrounded by 1\n", 24);
	return (-1);
}

int parse_map(int fd, t_index *m)
{
    char *line;

	line = "";
    m->parse.map_string = "";
	while (line[0] == '\0')
		get_next_line(fd, &line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
    while (get_next_line(fd, &line))
    {
        if (line[0] == '\0')
			write_error_one();
        m->parse.map_string = ft_strjoin(m->parse.map_string, line);
        m->parse.map_string = ft_strjoin(m->parse.map_string, "\n");
        free(line);
        line = NULL;
    }
    m->parse.map_string = ft_strjoin(m->parse.map_string, line);
	m->parse.map_string = ft_strjoin(m->parse.map_string, "\0");
	free(line);
	line = NULL;
    return (1);
}

int parse_data(int fd, t_index *m)
{
    char *line;
    int i;

    i = 0;
    m->parse.data = "";
    while (get_next_line(fd, &line) && i < 7)
    {
        if (line[0] == '\0')
			get_next_line(fd, &line);
        if (!ft_isdigit(line[0]))
        {
			m->parse.data = ft_strjoin(m->parse.data, line);
			m->parse.data = ft_strjoin(m->parse.data, "\n");
			free(line);
			line = NULL;
            i++;
        }
    }
	while (line[0] == '\0')
		get_next_line(fd, &line);
	m->parse.data = ft_strjoin(m->parse.data, line);
	m->parse.data = ft_strjoin(m->parse.data, "\0");
	free(line);
	line = NULL;
    return (1);
}

int parse_cub(t_index *m, char *filename)
{
	int		fd;
	
	fd = open(filename, O_RDONLY);
	if (parse_data(fd, m) < 0)
		return (-1);
    if (parse_map(fd, m) < 0)
        return (-1);
	close(fd);
	if (create_map(m) < 0)
		return (-1);
	if (create_good_size_map(m) < 0)
        return (-1);
	if (get_sprites(m) < 0)
		return (-1);
	if (get_elements(m) < 0)
		return (-1);
	if (check_elements_errors(m) < 0)
		return (-1);
	if (check_map_errors(m) < 0)
		return (-1);
	return (1);
}
