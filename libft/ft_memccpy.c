/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:11:12 by hbuisser          #+#    #+#             */
/*   Updated: 2019/10/25 14:15:50 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	p;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	p = (unsigned char)c;
	i = 0;
	while (i < n && (i == 0 || ((i > 0) && s[i - 1] != p)))
	{
		d[i] = s[i];
		i++;
	}
	if (i > 0 && s[i - 1] == p)
		return (d + i);
	else
		return (NULL);
}
