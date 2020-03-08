/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:08:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 19:29:16 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int write_error_ceilling(t_index *m, int i)
{
    if (m->el.elem[m->el.ceilling_line][i] == '\0' ||
        m->el.elem[m->el.ceilling_line][i] != ' ')
    {
        write(1, "Error\n", 6);
        write(1, "Wrong ceilling arguments\n", 16);
        exit(0);
    }
    return (-1);
}

int write_error_end_ceilling(t_index *m, int i)
{
    if (m->el.elem[m->el.ceilling_line][i] != ' ')
    {
        write(1, "Error\n", 6);
        write(1, "Wrong ceilling arguments\n", 16);
        exit(0);
    }
    return (-1);
}

int get_ceilling_color(t_index *m)
{
    int i;

    i = 0;
    while (m->el.elem[m->el.ceilling_line][++i] == ' ')
		i++;
    while (m->el.elem[m->el.ceilling_line][i] >= '0' && m->el.elem[m->el.ceilling_line][i] <= '9')
        m->el.ceilling_color_r = (m->el.ceilling_color_r * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.ceilling_line][++i] != ',')
        write_error_ceilling(m, i);
    while (!ft_isdigit(m->el.elem[m->el.ceilling_line][++i]))
        write_error_ceilling(m, i);
    while (m->el.elem[m->el.ceilling_line][i] >= '0' && m->el.elem[m->el.ceilling_line][i] <= '9')
        m->el.ceilling_color_g = (m->el.ceilling_color_g * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.ceilling_line][++i] != ',')
        write_error_ceilling(m, i);
    while (!ft_isdigit(m->el.elem[m->el.ceilling_line][++i]))
        write_error_ceilling(m, i);
    while (m->el.elem[m->el.ceilling_line][i] >= '0' && m->el.elem[m->el.ceilling_line][i] <= '9')
        m->el.ceilling_color_b = (m->el.ceilling_color_b * 10) + m->el.elem[m->el.ceilling_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.ceilling_line][++i] != '\0')
        write_error_end_ceilling(m, i);
    return (0);
}

int write_error_floor(t_index *m, int i)
{
    if (m->el.elem[m->el.floor_line][i] == '\0' ||
        m->el.elem[m->el.floor_line][i] != ' ')
    {
        write(1, "Error\n", 6);
        write(1, "Wrong arguments\n", 16);
        exit(0);
    }
    return (-1);
}

int write_error_end_floor(t_index *m, int i)
{
    if (m->el.elem[m->el.floor_line][i] != ' ')
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
    while (m->el.elem[m->el.floor_line][++i] == ' ')
		i++;
    while (m->el.elem[m->el.floor_line][i] >= '0' && m->el.elem[m->el.floor_line][i] <= '9')
        m->el.floor_color_r = (m->el.floor_color_r * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.floor_line][++i] != ',')
        write_error_floor(m, i);
    while (!ft_isdigit(m->el.elem[m->el.floor_line][++i]))
        write_error_floor(m, i);
    while (m->el.elem[m->el.floor_line][i] >= '0' && m->el.elem[m->el.floor_line][i] <= '9')
        m->el.floor_color_g = (m->el.floor_color_g * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.floor_line][++i] != ',')
        write_error_floor(m, i);
    while (!ft_isdigit(m->el.elem[m->el.floor_line][++i]))
        write_error_floor(m, i);
    while (m->el.elem[m->el.floor_line][i] >= '0' && m->el.elem[m->el.floor_line][i] <= '9')
        m->el.floor_color_b = (m->el.floor_color_b * 10) + m->el.elem[m->el.floor_line][i++] - '0';
    i = i - 1;
    while (m->el.elem[m->el.floor_line][++i] != '\0')
        write_error_end_floor(m, i);
    return (0);
}

int calcul_digit(t_index *m, int i)
{
	int	digit;

	digit = 0;
    while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
    while (m->el.elem[m->el.resolution_line][i] >= '0' &&
            m->el.elem[m->el.resolution_line][i] <= '9')
    {
        digit = (digit * 10) + m->el.elem[m->el.resolution_line][i] - '0';
        i++;
    }
    m->el.res_x = digit;
    return (i);
}

int write_error_res()
{
    write(1, "Error\n", 6);
    write(1, "Wrong arguments\n", 16);
    exit(0);
}

int get_resolution(t_index *m)
{
    int	i;
	int	digit;

	digit = 0;
    i = 1;
    i = calcul_digit(m, i);
    while (m->el.elem[m->el.resolution_line][i] == ' ')
		i++;
    if (m->el.elem[m->el.resolution_line][i] == '\0' ||
            !ft_isdigit(m->el.elem[m->el.resolution_line][i]))
        write_error_res();
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
            write_error_res();
        i++;
    }
    return (1);
}

void create_hex_color(t_index *m)
{
    m->el.c_color_hex = transform_to_hex(m->el.ceilling_color_r,
        m->el.ceilling_color_g, m->el.ceilling_color_b);
    m->el.f_color_hex = transform_to_hex(m->el.floor_color_r, 
        m->el.floor_color_g, m->el.floor_color_b);
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

int get_elements(t_index *m)
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
    if (!get_sprite_texture(m))
        return (-1);
    if (!get_north_texture(m))
        return (-1);
    if (!get_south_texture(m))
        return (-1);
    if (!get_west_texture(m))
        return (-1);
    if (!get_east_texture(m))
        return (-1);
    return (1);
}
