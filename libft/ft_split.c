/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:51:37 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/08 15:43:19 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_separator(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int		is_word(char s1, char s2, char c)
{
	if (!is_separator(s1, c) && is_separator(s2, c))
		return (1);
	else
		return (0);
}

static int		count_w(const char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (i == 0 || is_word(str[i], str[i - 1], c))
			count++;
		i++;
	}
	return (count);
}

char			*malloc_word(const char *str, char c)
{
	char*word;
	int i;

	i = 0;
	while (str[i] != '\0' && !is_separator(str[i], c))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] != '\0' && !is_separator(str[i], c))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char			**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL || c < 0)
		return (NULL);
	if (!(array = (char **)malloc(sizeof(char *) * count_w(s, c) + 1)))
		return (0);
	while (*s)
	{
		while (*s && is_separator(*s, c))
			s++;
		if (*s && !is_separator(*s, c))
		{
			if ((array[i] = malloc_word(s, c)) == NULL)
				return (ft_free(array, i));
			i++;
			while (*s && !is_separator(*s, c))
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
