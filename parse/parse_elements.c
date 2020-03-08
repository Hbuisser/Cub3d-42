/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:08:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 14:31:49 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_ceilling_color(t_index *m)
{
    int i;
    int digit;

    i = 1;
    digit = 0;
    while (m->el.elem[m->el.ceilling_line][++i] == ' ')
		i++;
    while (m->el.elem[m->el.ceilling_line][i] >= '0' &&
            m->el.elem[m->el.ceilling_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    m->el.ceilling_color_r = digit;
    while (m->el.elem[m->el.ceilling_line][i] != ',')
    {
        if (m->el.elem[m->el.ceilling_line][i] == '\0' ||
                m->el.elem[m->el.ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    digit = 0;
    i++;
    while (!ft_isdigit(m->el.elem[m->el.ceilling_line][i]))
    {
        if (m->el.elem[m->el.ceilling_line][i] == '\0' ||
                m->el.elem[m->el.ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    while (m->el.elem[m->el.ceilling_line][i] >= '0' &&
            m->el.elem[m->el.ceilling_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    m->el.ceilling_color_g = digit;
    while (m->el.elem[m->el.ceilling_line][i] != ',')
    {
        if (m->el.elem[m->el.ceilling_line][i] == '\0' ||
                m->el.elem[m->el.ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    i++;
    digit = 0;
    while (!ft_isdigit(m->el.elem[m->el.ceilling_line][i]))
    {
        if (m->el.elem[m->el.ceilling_line][i] == '\0' ||
                m->el.elem[m->el.ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    while (m->el.elem[m->el.ceilling_line][i] >= '0' &&
            m->el.elem[m->el.ceilling_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    m->el.ceilling_color_b = digit;
    while (m->el.elem[m->el.ceilling_line][i] != '\0')
    {
        if (m->el.elem[m->el.ceilling_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong ceilling arguments\n", 34);
            return (-1);
        }
        i++;
    }
    return (0);
}

int get_floor_color(t_index *m)
{
    int i;
    int digit;

    i = 1;
    digit = 0;
    while (m->el.elem[m->el.floor_line][++i] == ' ')
		i++;
    while (m->el.elem[m->el.floor_line][i] >= '0' &&
            m->el.elem[m->el.floor_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    m->el.floor_color_r = digit;
    while (m->el.elem[m->el.floor_line][i] != ',')
    {
        if (m->el.elem[m->el.floor_line][i] == '\0' ||
                m->el.elem[m->el.floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    digit = 0;
    i++;
    while (!ft_isdigit(m->el.elem[m->el.floor_line][i]))
    {
        if (m->el.elem[m->el.floor_line][i] == '\0' ||
                m->el.elem[m->el.floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    while (m->el.elem[m->el.floor_line][i] >= '0' &&
            m->el.elem[m->el.floor_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    m->el.floor_color_g = digit;
    while (m->el.elem[m->el.floor_line][i] != ',')
    {
        if (m->el.elem[m->el.floor_line][i] == '\0' ||
                m->el.elem[m->el.floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    i++;
    digit = 0;
    while (!ft_isdigit(m->el.elem[m->el.floor_line][i]))
    {
        if (m->el.elem[m->el.floor_line][i] == '\0' ||
                m->el.elem[m->el.floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments\n", 34);
                return (-1);
        }
        i++; 
    }
    while (m->el.elem[m->el.floor_line][i] >= '0' &&
            m->el.elem[m->el.floor_line][i] <= '9')
        digit = (digit * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    m->el.floor_color_b = digit;
    while (m->el.elem[m->el.floor_line][i] != '\0')
    {
        if (m->el.elem[m->el.floor_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong floor arguments\n", 34);
            return (-1);
        }
        i++;
    }
    return (0);
}

int get_resolution(t_index *m)
{
    int	i;
	int	digit;

	digit = 0;
    i = 1;
    while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
    while (m->el.elem[m->el.resolution_line][i] >= '0' &&
            m->el.elem[m->el.resolution_line][i] <= '9')
    {
        digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
        i++;
    }
    m->el.res_x = digit;
    digit = 0;
    while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
    if (m->el.elem[m->el.resolution_line][i] == '\0' ||
            !ft_isdigit(m->el.elem[m->el.resolution_line][i]))
    {
            write(1, "Error\n", 6);
            write(1, "--> Wrong resolution arguments\n", 31);
            return (-1);
    }  
    while (m->el.elem[m->el.resolution_line][i] >= '0' &&
            m->el.elem[m->el.resolution_line][i] <= '9')
    {
        digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
        i++;
    }
    m->el.res_y = digit;
    while (m->el.elem[m->el.resolution_line][i] != '\0')
    {
        if (m->el.elem[m->el.resolution_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong resolution arguments\n", 31);
            return (-1);
        }
        i++;
    }
    return (0);
}

void    check_letters(t_index *m, int i, int j)
{
    if (m->el.elem[i][j] == 'R')
        m->el.resolution_line = i;
    if (m->el.elem[i][j] == 'N')
        m->el.north_line = i;
    if (m->el.elem[i][j] == 'S')
    {
        if (m->el.elem[i][j + 1] == 'O')
            m->el.south_line = i;
        else
            m->el.sprite_line = i;
    }
    if (m->el.elem[i][j] == 'W')
        m->el.west_line = i;
    if (m->el.elem[i][j] == 'E')
        m->el.east_line = i;
    if (m->el.elem[i][j] == 'F')
        m->el.floor_line = i;
    if (m->el.elem[i][j] == 'C')
        m->el.ceilling_line = i;
}

void create_elements_lines(t_index *m)
{
    int i;
    int j;

    i = 0;
    while (m->el.elem[i] != NULL)
    {
        j = 0;
        while (m->el.elem[i][j] != '\0')
        {
            check_letters(m, i, j);
            j++;
        }
        i++;
    }
}

void create_hex_color(t_index *m)
{
    m->el.c_color_hex = transform_to_hex(m->el.ceilling_color_r,
        m->el.ceilling_color_g, m->el.ceilling_color_b);
    m->el.f_color_hex = transform_to_hex(m->el.floor_color_r, 
        m->el.floor_color_g, m->el.floor_color_b);
}

int create_elements(t_index *m)
{
    m->el.elem = ft_strsplit(m->parse.data, '\n');
    create_elements_lines(m);
    if (get_resolution(m) < 0)
        return (-1);
    if (get_floor_color(m) < 0)
        return (-1);
    if (get_ceilling_color(m) < 0)
        return (-1);
    create_hex_color(m);
    get_sprite_texture(m);
    get_north_texture(m);
    get_south_texture(m);
    get_west_texture(m);
    get_east_texture(m);
    return (0);
}
