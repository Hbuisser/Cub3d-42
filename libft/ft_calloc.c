/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:22:01 by hbuisser          #+#    #+#             */
/*   Updated: 2019/10/23 11:45:31 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	if (size == 0 || count == 0)
	{
		size = 1;
		count = 1;
	}
	if (!(ptr = (char *)malloc(sizeof(char) * (size * count))))
		return (0);
	i = 0;
	ft_bzero(ptr, count * size);
	return (ptr);
}
