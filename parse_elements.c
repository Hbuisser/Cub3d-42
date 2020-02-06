/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:08:53 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/06 12:41:25 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_ceilling_color(t_index *idx)
{
    int i;
    int digit;

    i = 1;
    digit = 0;
    while (idx->el->elem[idx->el->ceilling_line][++i] == ' ')
		i++;
    while (idx->el->elem[idx->el->ceilling_line][i] >= '0' &&
            idx->el->elem[idx->el->ceilling_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->ceilling_line][i++] - '0';
    idx->el->ceilling_color.rgb.r = digit;
    while (idx->el->elem[idx->el->ceilling_line][i] != ',')
    {
        if (idx->el->elem[idx->el->ceilling_line][i] == '\0' ||
                idx->el->elem[idx->el->ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments", 33);
                return (-1);
        }
        i++; 
    }
    digit = 0;
    i++;
    while (!ft_isdigit(idx->el->elem[idx->el->ceilling_line][i]))
    {
        if (idx->el->elem[idx->el->ceilling_line][i] == '\0' ||
                idx->el->elem[idx->el->ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments", 33);
                return (-1);
        }
        i++; 
    }
    while (idx->el->elem[idx->el->ceilling_line][i] >= '0' &&
            idx->el->elem[idx->el->ceilling_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->ceilling_line][i++] - '0';
    idx->el->ceilling_color.rgb.g = digit;
    while (idx->el->elem[idx->el->ceilling_line][i] != ',')
    {
        if (idx->el->elem[idx->el->ceilling_line][i] == '\0' ||
                idx->el->elem[idx->el->ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments", 33);
                return (-1);
        }
        i++; 
    }
    i++;
    digit = 0;
    while (!ft_isdigit(idx->el->elem[idx->el->ceilling_line][i]))
    {
        if (idx->el->elem[idx->el->ceilling_line][i] == '\0' ||
                idx->el->elem[idx->el->ceilling_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong ceilling arguments", 33);
                return (-1);
        }
        i++; 
    }
    while (idx->el->elem[idx->el->ceilling_line][i] >= '0' &&
            idx->el->elem[idx->el->ceilling_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->ceilling_line][i++] - '0';
    idx->el->ceilling_color.rgb.b = digit;
    while (idx->el->elem[idx->el->ceilling_line][i] != '\0')
    {
        if (idx->el->elem[idx->el->ceilling_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong ceilling arguments", 33);
            return (-1);
        }
        i++;
    }
    return (0);
}

int get_floor_color(t_index *idx)
{
    int i;
    int digit;

    i = 1;
    digit = 0;
    while (idx->el->elem[idx->el->floor_line][++i] == ' ')
		i++;
    while (idx->el->elem[idx->el->floor_line][i] >= '0' &&
            idx->el->elem[idx->el->floor_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->floor_line][i++] - '0';
    idx->el->floor_color.rgb.r = digit;
    while (idx->el->elem[idx->el->floor_line][i] != ',')
    {
        if (idx->el->elem[idx->el->floor_line][i] == '\0' ||
                idx->el->elem[idx->el->floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments", 30);
                return (-1);
        }
        i++; 
    }
    digit = 0;
    i++;
    while (!ft_isdigit(idx->el->elem[idx->el->floor_line][i]))
    {
        if (idx->el->elem[idx->el->floor_line][i] == '\0' ||
                idx->el->elem[idx->el->floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments", 30);
                return (-1);
        }
        i++; 
    }
    while (idx->el->elem[idx->el->floor_line][i] >= '0' &&
            idx->el->elem[idx->el->floor_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->floor_line][i++] - '0';
    idx->el->floor_color.rgb.g = digit;
    while (idx->el->elem[idx->el->floor_line][i] != ',')
    {
        if (idx->el->elem[idx->el->floor_line][i] == '\0' ||
                idx->el->elem[idx->el->floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments", 30);
                return (-1);
        }
        i++; 
    }
    i++;
    digit = 0;
    while (!ft_isdigit(idx->el->elem[idx->el->floor_line][i]))
    {
        if (idx->el->elem[idx->el->floor_line][i] == '\0' ||
                idx->el->elem[idx->el->floor_line][i] != ' ')
        {
                write(1, "Error\n", 6);
                write(1, "--> Wrong floor arguments", 30);
                return (-1);
        }
        i++; 
    }
    while (idx->el->elem[idx->el->floor_line][i] >= '0' &&
            idx->el->elem[idx->el->floor_line][i] <= '9')
        digit = (digit * 10) + idx->el->elem[idx->el->floor_line][i++] - '0';
    idx->el->floor_color.rgb.b = digit;
    while (idx->el->elem[idx->el->floor_line][i] != '\0')
    {
        if (idx->el->elem[idx->el->floor_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong resolution arguments", 30);
            return (-1);
        }
        i++;
    }
    return (0);
}

int get_resolution(t_index *idx)
{
    int	i;
	int	digit;

	digit = 0;
    i = 1;
    while (idx->el->elem[idx->el->resolution_line][i] == ' ')
		i++;
    while (idx->el->elem[idx->el->resolution_line][i] >= '0' &&
            idx->el->elem[idx->el->resolution_line][i] <= '9')
    {
        digit = (digit * 10) + idx->el->elem[idx->el->resolution_line][i] - '0';
        i++;
    }
    idx->el->resolution_x = digit;
    digit = 0;
    while (idx->el->elem[idx->el->resolution_line][i] == ' ')
		i++;
    if (idx->el->elem[idx->el->resolution_line][i] == '\0' ||
            !ft_isdigit(idx->el->elem[idx->el->resolution_line][i]))
    {
            write(1, "Error\n", 6);
            write(1, "--> Wrong resolution arguments", 30);
            return (-1);
    }  
    while (idx->el->elem[idx->el->resolution_line][i] >= '0' &&
            idx->el->elem[idx->el->resolution_line][i] <= '9')
    {
        digit = (digit * 10) + idx->el->elem[idx->el->resolution_line][i] - '0';
        i++;
    }
    idx->el->resolution_y = digit;
    while (idx->el->elem[idx->el->resolution_line][i] != '\0')
    {
        if (idx->el->elem[idx->el->resolution_line][i] != ' ')
        {
            write(1, "Error\n", 6);
            write(1, "--> Wrong resolution arguments", 30);
            return (-1);
        }
        i++;
    }
    return (0);
}

void create_elements_lines(t_index *idx)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (idx->el->elem[i] != NULL)
    {
        j = 0;
        while (idx->el->elem[i][j] != '\0')
        {
            if (idx->el->elem[i][j] == 'R')
                idx->el->resolution_line = i;
            else if (idx->el->elem[i][j] == 'N')
                idx->el->north_line = i;
            else if (idx->el->elem[i][j] == 'S')
            {
                if (idx->el->elem[i][j + 1] == 'O')
                    idx->el->south_line = i;
                else
                    idx->el->sprite_line = i;
            }
            else if (idx->el->elem[i][j] == 'W')
                idx->el->west_line = i;
            else if (idx->el->elem[i][j] == 'E')
                idx->el->east_line = i;
            else if (idx->el->elem[i][j] == 'F')
                idx->el->floor_line = i;
            else if (idx->el->elem[i][j] == 'C')
                idx->el->ceilling_line = i;
            j++;
        }
        i++;
    }
}

int create_elements(t_index *idx)
{
    idx->el->elem = ft_split(idx->parse->data, '\n');
    create_elements_lines(idx);
    if (get_resolution(idx) < 0)
        return (-1);
    if (get_floor_color(idx) < 0)
        return (-1);
    if (get_ceilling_color(idx) < 0)
        return (-1);
    get_sprite_texture(idx);
    get_north_texture(idx);
    get_south_texture(idx);
    get_west_texture(idx);
    get_east_texture(idx);
    check_elements_errors(idx);
    /*printf("%s\n", idx->el->n_path);
    printf("%s\n", idx->el->s_path);
    printf("%s\n", idx->el->e_path);
    printf("%s\n", idx->el->w_path);*/
    return (0);
}
