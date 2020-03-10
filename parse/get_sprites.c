/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 15:03:45 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/10 19:48:59 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		malloc_size_sprite(t_index *m)
{
	if (!(m->spr.sprites_x = malloc(sizeof(int *) * m->spr.numsprites + 1)))
	{
		write(1, "Error\n", 6);
		write(1, "Can't malloc the sprite", 23);
		exit_all(m);
		return (-1);
	}
	if (!(m->spr.sprites_y = malloc(sizeof(int *) * m->spr.numsprites + 1)))
	{
		write(1, "Error\n", 6);
		write(1, "Can't malloc the sprite", 23);
		exit_all(m);
		return (-1);
	}
	return (1);
}

void	parse_sprites(t_index *m)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (m->parse.map[i] != NULL)
	{
		j = 0;
		while (m->parse.map[i][j] != '\0')
		{
			if (m->parse.map[i][j] == '2')
			{
				m->spr.sprites_x[k] = j + 0.5;
				m->spr.sprites_y[k] = i + 1;
				k++;
			}
			j++;
		}
		i++;
	}
}

int		get_sprites(t_index *m)
{
	if (malloc_size_sprite(m) < 0)
		return (-1);
	parse_sprites(m);
	return (1);
}
