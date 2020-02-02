/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:32:32 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/02 18:55:49 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_stat(char **stat, int result)
{
	if (*stat)
	{
		free(*stat);
		*stat = 0;
	}
	return (result);
}

int		ft_strnbr(char *stat)
{
	int i;

	i = 0;
	while (stat[i] != '\0')
	{
		if (stat[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strnew(int end)
{
	char *tmp;

	if (!(tmp = (char *)malloc(sizeof(char) * 1)))
		return (0);
	tmp[0] = end;
	return (tmp);
}

int		ft_line_creation(char **stat, char **line, int idx)
{
	char	*tmp;
	int		result;

	if (idx >= 0)
	{
		if (!(*line = ft_substr(*stat, 0, idx)))
			return (ft_free_stat(stat, -1));
		if (!(tmp = ft_substr(*stat, idx + 1, (ft_strlen(*stat) - idx - 1))))
			return (ft_free_stat(stat, -1));
		result = 1;
	}
	else
	{
		if (!(*line = ft_substr(*stat, 0, ft_strlen(*stat))))
			return (ft_free_stat(stat, -1));
		result = 0;
		tmp = 0;
	}
	ft_free_stat(stat, 0);
	*stat = tmp;
	return (result);
}

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	static char	*stat;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (ft_free_stat(&stat, -1));
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!(tmp = ft_strnjoin_gnl(stat, buff, ret)))
			return (ft_free_stat(&stat, -1));
		ft_free_stat(&stat, 0);
		stat = tmp;
		if (ft_strnbr(stat) >= 0)
			break ;
	}
	if (ret < 0)
		return (ft_free_stat(&stat, -1));
	if (ret == 0 && (!stat || *stat == '\0') &&
			(*line = ft_strnew('\0')))
		return (ft_free_stat(&stat, 0));
	return (ft_line_creation(&stat, line, ft_strnbr(stat)));
}
