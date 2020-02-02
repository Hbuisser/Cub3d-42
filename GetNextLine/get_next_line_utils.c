/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:32:52 by hbuisser          #+#    #+#             */
/*   Updated: 2019/12/18 16:33:26 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*dest;
	int		i;

	if (len < 0 || s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(dest = (char *)malloc(sizeof(char))))
			return (0);
		dest[0] = '\0';
		return (dest);
	}
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	i = 0;
	while (len > 0)
	{
		dest[i] = s[i + start];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	if (!(s2 = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (0);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strnjoin(char *s1, char *s2, int ret)
{
	int		len;
	char	*result;
	int		i;

	len = ft_strlen(s1) + ret;
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2 && *s2 != '\0')
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}
