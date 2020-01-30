/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:46:57 by hbuisser          #+#    #+#             */
/*   Updated: 2019/10/19 14:13:03 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		len;

	len = ft_strlen(s);
	ptr = (char *)s + len - 1;
	if (c == '\0')
		return (ptr + 1);
	while (len > 0)
	{
		if (*ptr == c)
			return (ptr);
		ptr--;
		len--;
	}
	if (c == '\0')
	{
		ptr++;
		return (ptr);
	}
	return (NULL);
}
