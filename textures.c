/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:35:19 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/15 14:44:53 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    calculate_colors(t_index *idx)
{
    idx->tex->color_n = mlx_get_data_addr(idx->tex->color_n, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    idx->tex->color_s = mlx_get_data_addr(idx->tex->color_s, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    idx->tex->color_w = mlx_get_data_addr(idx->tex->color_w, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    idx->tex->color_e = mlx_get_data_addr(idx->tex->color_e, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);
    idx->spr->spr_tex = mlx_get_data_addr(idx->spr->spr_tex, &idx->img->bits_per_pixel, &idx->img->line_length, &idx->img->endian);

    // color in textures
    if (idx->big->side == 1 && (idx->big->mapY > idx->big->posY))
        idx->tex->color = (int *)idx->tex->color_n;
    else if (idx->big->side == 1 && (idx->big->mapY < idx->big->posY))
        idx->tex->color = (int *)idx->tex->color_w;
    else if (idx->big->side == 0 && (idx->big->mapX > idx->big->posX))
        idx->tex->color = (int *)idx->tex->color_s;
    else
        idx->tex->color = (int *)idx->tex->color_e;
    
    // color in sprite
    idx->spr->color = (int *)idx->spr->spr_tex;
}

void	calculate_textures(t_index *idx)
{
    double	wallX;

    if (idx->big->side == 0) 
        wallX = idx->big->posY + idx->big->perpWallDist * idx->big->rayDirY;
    else
        wallX = idx->big->posX + idx->big->perpWallDist * idx->big->rayDirX;
    wallX -= floor((wallX));
    idx->tex->texX = (int)(wallX * idx->tex->texHeight);
    if (idx->big->side == 0 && idx->big->rayDirX > 0)
		idx->tex->texX = idx->tex->texWidth - idx->tex->texX - 1;
    if (idx->big->side == 1 && idx->big->rayDirY < 0)
		idx->tex->texX = idx->tex->texWidth - idx->tex->texX - 1;
	// How much to increase the texture coordinate per screen pixel
	idx->tex->step = 1.0 * idx->tex->texHeight / idx->big->lineHeight;
	// Starting texture coordinate
	idx->tex->texPos = (idx->big->drawStart - idx->el->resolution_y / 2 + idx->big->lineHeight / 2) * idx->tex->step;
}

int generate_textures(t_index *idx)
{
    if (!(idx->tex->color_n = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->n_path, &idx->tex->texWidth, &idx->tex->texWidth)))
    {
        write (1, "n wrong path texture\n", 20);
        return (-1);
    }
	if (!(idx->tex->color_s = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->s_path, &idx->tex->texWidth, &idx->tex->texHeight)))
    {
        write (1, "wrong path texture", 18);
        return (-1);
    }
	if (!(idx->tex->color_w = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->w_path, &idx->tex->texWidth, &idx->tex->texHeight)))
    {
        write (1, "wrong path texture", 18);
        return (-1);
    }
	if (!(idx->tex->color_e = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->e_path, &idx->tex->texWidth, &idx->tex->texHeight)))
    {
        write (1, "wrong path texture", 18);
        return (-1);
    }
    if (!(idx->spr->spr_tex = mlx_xpm_file_to_image(idx->window->mlx_ptr, idx->el->spr_path, &idx->spr->sprWidth, &idx->spr->sprHeight)))
    {
        write (1, "texture of the sprite is wrong", 30);
        return (-1);
    }
    return (0);
}
