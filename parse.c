/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:15:48 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 11:23:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int parse_data_and_map(t_index *idx, char *filename)
{
	char	*map_string;
	char 	*map_string_clean;
	char 	*data;
	char 	*line;
	int		fd;
	int 	i;
	int 	j;
	int 	count;
	
	//big->ceiling_color.hexcode = 0;
	//big->floor_color.hexcode = 0;
	map_string = "";
	data = "";
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == '\0')
			get_next_line(fd, &line);
		if (line[0] != '1')
		{
			data = ft_strjoin(data, line);
			data = ft_strjoin(data, "\n");
			free(line);
			line = NULL;
		}
		else
		{
			map_string = ft_strjoin(map_string, line);
			map_string = ft_strjoin(map_string, "\n");
			free(line);
			line = NULL;
		}
	}
	map_string = ft_strjoin(map_string, line);
	map_string = ft_strjoin(map_string, "\0");
	free(line);
	line = NULL;
	close(fd);
	i = 0;
	count = 0;
	while (map_string[i] != '\0')
	{
		if (map_string[i] != ' ')
			count++;
		i++;
	}
	i = 0;
	j = 0;
	if (!(map_string_clean = malloc(sizeof(char) * count + 1)))
		return (0);
	while (map_string[i] != '\0')
	{
		if (map_string[i] != ' ')
		{
			map_string_clean[j] = map_string[i];
			j++; 
		}
		i++;
	}
	map_string_clean[j] = '\0';
	printf("%s\n", map_string_clean);


	idx->big->map = ft_split(map_string_clean, '\n');
	i = 0;
	/*while (i < 14)
	{
		printf("%s\n", *idx->big->map);
		idx->big->map++;
		i++;
	}*/
	j = 0;
	while (idx->big->map[i] != NULL)
	{
		j = 0;
		while (idx->big->map[i][j] != '\0')
		{
			if ((ft_isalpha(idx->big->map[i][j])))
			{
				idx->big->posX = j;
				idx->big->posY = i;
				printf("%i%i", i, j);
			}
			j++;
		}
		i++;
	}
	//printf("%f\n", idx->big->posX);
	return (1);
}












///////////////// bsq parsing

/*char	*get_next_line(char *str, t_info *info)
{
	int i;
	char*ret;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!(ret = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	if (str[i] == '\n' || str[i] == '\0')
		info->count++;
	ret[i] = '\0';
	return (ret);
}

char	**read_and_store(char *begin, char **tab, t_info *info)
{
	int	i;

	i = 0;
	if (!(tab = malloc(sizeof(char*) * (info->lines + 1))))
		return (NULL);
	while (i < info->lines)
	{
		tab[i] = NULL;
		i++;
	}
	i = 0;
	while (i < info->lines)
	{
		tab[i] = get_next_line(begin, info);
		begin += ft_strlen(tab[i]) + 1;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**get_info(char *str, char **tab, t_info *info)
{
	char*buff;
	char*temp;
	int i;

	i = 0;
	if (tab != NULL)
		free_tab(tab, info);
	if (!(buff = get_file(str)))
		return (NULL);
	if (!(temp = get_first_line(buff)))
		return (NULL);
	i = ft_strlen(temp) - 1;
	info->plein = temp[i--];
	info->obstacle = temp[i--];
	info->vide = temp[i];
	temp[i] = '\0';
	info->lines = ft_atoi(temp);
	if (info->lines == 0 || info->obstacle == info->vide ||
		info->obstacle == info->plein || info->vide == info->plein)
		return (NULL);
	while (buff[i] != '\n')
		i++;
	tab = read_and_store((buff + i + 1), tab, info);
	return (tab);
}

int	**get_sim(char **tab, t_info *info)
{
	int	**ret;
	int	i;
	int j;
	int len;

	ret = (int **)malloc(sizeof(int *) * info->lines);
	len = ft_strlen(tab[0]);
	i = 0;
	while (++i < info->lines)
	{
		ret[i] = (int*)malloc(sizeof(int) * len);
		j = 0;
		while (++j < len)
		{
			if (tab[i][j] == info->obstacle)
				ret[i][j] = 4;
			else
				ret[i][j] = 0;
		}
	}
	ret = get_special(tab, info, ret);
	return (ret);
}

int	**get_special(char **tab, t_info *info, int **ret)
{
	int len;
	int i;

	len = ft_strlen(tab[0]);
	ret[0] = (int*)malloc(sizeof(int) * len);
	i = -1;
	while (++i < len)
	{
		if (tab[0][i] == info->obstacle)
			ret[0][i] = 0;
		else
			ret[0][i] = 1;
	}
	i = 1;
	while (i < info->lines)
	{
		if (tab[i][0] == info->obstacle)
			ret[i][0] = 0;
		else
			ret[i][0] = 1;
		i++;
	}
	return (ret);
}

char	*get_first_line(char *str)
{
	int i;
	char*ret;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}



char	*get_file(char *str)
{
	int	fd;
	char*buff;
	int	red;
	int first;
	char*ret;

	first = 1;
	if ((fd = open(str, O_RDONLY)) == -1)
		return (NULL);
	if (!(buff = malloc(sizeof(char) * (BUF_SIZE + 1))))
		return (NULL);
	while ((red = read(fd, buff, BUF_SIZE)) != 0)
	{
		buff[red] = '\0';
		if (first-- == 1)
			ret = ft_strdup(buff);
		else
			ret = ft_strcat(ret, buff);
	}
	free(buff);
	if (close(fd) == -1)
		return (NULL);
	return (ret);
}

char	*get_std(void)
{
	char*buff;
	int	red;
	int first;
	char*ret;
	int	input;

	first = 1;
	input = 0;
	if (!(buff = malloc(sizeof(char) * (BUF_SIZE + 1))))
		return (NULL);
	while ((red = read(0, buff, BUF_SIZE)) != 0)
	{
		input++;
		buff[red] = '\0';
		if (first-- == 1)
			ret = ft_strdup(buff);
		else
			ret = ft_strcat(ret, buff);
	}
	free(buff);
	if (!input)
		return (NULL);
	return (ret);
}

char	**get_info_std(char **tab, t_info *info)
{
	char*buff;
	char*temp;
	int i;

	i = 0;
	if (tab != NULL)
		free_tab(tab, info);
	if (!(buff = get_std()))
		return (NULL);
	if (!(temp = get_first_line(buff)))
		return (NULL);
	i = ft_strlen(temp) - 1;
	info->plein = temp[i--];
	info->obstacle = temp[i--];
	info->vide = temp[i];
	temp[i] = '\0';
	info->lines = ft_atoi(temp);
	if (info->lines == 0 || info->obstacle == info->vide ||
		info->obstacle == info->plein || info->vide == info->plein)
		return (NULL);
	while (buff[i] != '\n')
		i++;
	tab = read_and_store((buff + i + 1), tab, info);
	free(buff);
	return (tab);
}*/
