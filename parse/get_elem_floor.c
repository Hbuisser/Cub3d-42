/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 19:44:36 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 19:46:36 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int write_error_floor(t_index *m, int i)
{
    if (m->el.elem[m->el.f_l][i] == '\0' ||
        m->el.elem[m->el.f_l][i] != ' ')
    {
        write(1, "Error\n", 6);
        write(1, "Wrong arguments\n", 16);
        exit(0);
    }
    return (-1);
}

int write_error_end_floor(t_index *m, int i)
{
    if (m->el.elem[m->el.f_l][i] != ' ')
    {
        write(1, "Error\n", 6);
        write(1, "Wrong arguments\n", 16);
        exit(0);
    }
    return (-1);
}

int get_floor_color(t_index *m)
{
    int i;

    i = 0;
    while (m->el.elem[m->el.f_l][++i] == ' ')
		i++;
    while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
        m->el.f_r = (m->el.f_r * 10) + m->el.elem[m->el.f_l][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.f_l][++i] != ',')
        write_error_floor(m, i);
    while (!ft_isdigit(m->el.elem[m->el.f_l][++i]))
        write_error_floor(m, i);
    while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
        m->el.f_g = (m->el.f_g * 10) + m->el.elem[m->el.f_l][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.f_l][++i] != ',')
        write_error_floor(m, i);
    while (!ft_isdigit(m->el.elem[m->el.f_l][++i]))
        write_error_floor(m, i);
    while (m->el.elem[m->el.f_l][i] >= '0' && m->el.elem[m->el.f_l][i] <= '9')
        m->el.f_b = (m->el.f_b * 10) + m->el.elem[m->el.f_l][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.f_l][++i] != '\0')
        write_error_end_floor(m, i);
    return (0);
}
