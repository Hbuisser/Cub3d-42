/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:58:35 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 13:17:42 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_nbwords(const char *s, char c)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (*s != '\0')
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			nb++;
		}
		s++;
	}
	return (nb);
}

static int	ft_wordlen(const char *s, char c, int i)
{
	int		len;

	len = 0;
	while (s[i + len] != c && s[i + len] != '\0')
		len++;
	return (len);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**tab;
	int		i;
	int		k;
	int		len;
	int		nb_words;

	if (!s || !c)
		return (NULL);
	i = -1;
	k = 0;
	nb_words = ft_nbwords((const char *)s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (nb_words + 1))))
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			len = ft_wordlen(s, c, i);
			if (!(tab[k++] = ft_substr(s, i, len)))
				return (ft_free(tab, k));
			i = i + len - 1;
		}
	}
	tab[k] = NULL;
	return (tab);
}
