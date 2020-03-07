/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 16:35:19 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 13:49:15 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_colors(t_index *m)
{
	if (m->big.side == 1 && (m->big.mapY > m->big.posY))
		m->tex.color = (int *)m->tex.color_s;
	else if (m->big.side == 1 && (m->big.mapY < m->big.posY))
		m->tex.color = (int *)m->tex.color_n;
	else if (m->big.side == 0 && (m->big.mapX > m->big.posX))
		m->tex.color = (int *)m->tex.color_e;
	else
		m->tex.color = (int *)m->tex.color_w;
	m->spr.color = (int *)m->spr.spr_tex;
}

void	calculate_textures(t_index *m)
{
	float	wallx;

	if (m->big.side == 0)
		wallx = m->big.posY + m->big.perpWallDist * m->big.rayDirY;
	else
		wallx = m->big.posX + m->big.perpWallDist * m->big.rayDirX;
	wallx -= floor((wallx));
	m->tex.texX = (int)(wallx * m->tex.texHeight);
	if (m->big.side == 0 && m->big.rayDirX > 0)
		m->tex.texX = m->tex.texWidth - m->tex.texX - 1;
	if (m->big.side == 1 && m->big.rayDirY < 0)
		m->tex.texX = m->tex.texWidth - m->tex.texX - 1;
	m->tex.step = 1.0 * m->tex.texHeight / m->big.lineHeight;
	m->tex.texPos = (m->big.drawStart - m->el.res_y / 2 + m->big.lineHeight / 2)
		* m->tex.step;
}

int		create_images2(t_index *m)
{
	if (!(m->tex.color_e = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.e_path,
		&m->tex.texWidth, &m->tex.texHeight)))
	{
		write(1, "wrong path texture", 18);
		return (-1);
	}
	if (!(m->spr.spr_tex = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.spr_path,
		&m->spr.sprWidth, &m->spr.sprHeight)))
	{
		write(1, "texture of the sprite is wrong", 30);
		return (-1);
	}
	return (1);
}

int		create_images1(t_index *m)
{
	if (!(m->tex.color_n = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.n_path,
		&m->tex.texWidth, &m->tex.texWidth)))
	{
		write(1, "n wrong path texture\n", 20);
		return (-1);
	}
	if (!(m->tex.color_s = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.s_path,
		&m->tex.texWidth, &m->tex.texHeight)))
	{
		write(1, "wrong path texture", 18);
		return (-1);
	}
	if (!(m->tex.color_w = mlx_xpm_file_to_image(m->win.mlx_ptr, m->el.w_path,
		&m->tex.texWidth, &m->tex.texHeight)))
	{
		write(1, "wrong path texture", 18);
		return (-1);
	}
	return (1);
}

int		generate_textures(t_index *m)
{
	create_images1(m);
	create_images2(m);
	m->tex.color_n = mlx_get_data_addr(m->tex.color_n,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->tex.color_s = mlx_get_data_addr(m->tex.color_s,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->tex.color_w = mlx_get_data_addr(m->tex.color_w,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->tex.color_e = mlx_get_data_addr(m->tex.color_e,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	m->spr.spr_tex = mlx_get_data_addr(m->spr.spr_tex,
		&m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	return (0);
}
