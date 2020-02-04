/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:08:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/04 17:30:01 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void get_resolution(t_index *idx)
{
    int	i;
    //int	j;
	int	digit;

	digit = 0;
    i = 0;
    while (idx->elements->elem[idx->elements->resolution_line][i] != '\0')
    {
        if (ft_isdigit(idx->elements->elem[idx->elements->resolution_line][i]))
        {
            while (idx->elements->elem[idx->elements->resolution_line][i] != ' ')
            {
				digit = (digit * 10) + (idx->elements->elem[idx->elements->resolution_line][i]);
				idx->elements->resolution_x = digit;
                i++;
            }
            if (idx->elements->elem[idx->elements->resolution_line][i] != ' ')
                break ;
        }
        i++;
    }
	printf("%i\n", idx->elements->resolution_x);
}

void create_elements(t_index *idx)
{
    int i;
    int j;

    i = 0;
    j = 0;
    idx->elements->elem = ft_split(idx->parse->data, '\n');
    while (idx->elements->elem[i] != NULL)
    {
        j = 0;
        while (idx->elements->elem[i][j] != '\0')
        {
            if (idx->elements->elem[i][j] == 'R')
                idx->elements->resolution_line = i;
            else if (idx->elements->elem[i][j] == 'N')
                idx->elements->north_line = i;
            else if (idx->elements->elem[i][j] == 'S')
            {
                if (idx->elements->elem[i][j + 1] == 'O')
                    idx->elements->south_line = i;
                else
                    idx->elements->sprite_line = i;
            }
            else if (idx->elements->elem[i][j] == 'W')
                idx->elements->west_line = i;
            else if (idx->elements->elem[i][j] == 'E')
                idx->elements->east_line = i;
            else if (idx->elements->elem[i][j] == 'F')
                idx->elements->floor_line = i;
            else if (idx->elements->elem[i][j] == 'C')
                idx->elements->ceilling_line = i;
            j++;
        }
        i++;
    }
    get_resolution(idx);
    /*while (i < 8)
	{
		printf("%s\n", *idx->elements->elem);
		idx->elements->elem++;
		i++;
	}*/
}
