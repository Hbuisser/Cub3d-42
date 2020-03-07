/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 13:27:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_data(t_index *m)
{
	m->big.posX = m->parse.pos_x_init;
	m->big.posY = m->parse.pos_y_init;
	if (m->parse.dir == 'E')
	{
		m->big.planeX = 0;
		m->big.planeY = 1.4;
		m->big.dirX = 1;
		m->big.dirY = 0;
	}
	else if (m->parse.dir == 'W')
	{
		m->big.planeX = 0;
		m->big.planeY = -1.4;
		m->big.dirX = -1;
		m->big.dirY = 0;
	}
	else if (m->parse.dir == 'S')
	{
		m->big.planeX = -1.4;
		m->big.planeY = 0;
		m->big.dirX = 0;
		m->big.dirY = 1;
	}
	else if (m->parse.dir == 'N')
	{
		m->big.planeX = 1.4;
		m->big.planeY = 0;
		m->big.dirX = 0;
		m->big.dirY = -1;
	}
	m->tex.texWidth = 64;
	m->tex.texHeight = 64;
	m->spr.sprWidth = 0;
	m->spr.sprHeight = 0;
	m->big.moveSpeed = 0.2;
	m->big.rotSpeed = 0.04;
	if (!(m->spr.ZBuffer = malloc(sizeof(float *) * m->el.res_x + 1)))
		return (-1);
	return (1);
}

void init_1(t_index *m)
{
    m->big.cameraX = 0;
    m->big.mapX = 0;
    m->big.rayDirY = 0;
    m->big.rayDirX = 0;
	m->big.rayDirY = 0;
    m->big.mapX = 0;
	m->big.mapY = 0;
	m->big.sideDistX = 0;
    m->big.sideDistY = 0;
	m->big.deltaDistX = 0;
    m->big.deltaDistY = 0;
	m->big.perpWallDist = 0;
	m->big.stepX = 0;
    m->big.stepY = 0;
    m->big.drawStart = 0;
    m->big.drawEnd = 0;
    m->big.lineHeight = 0;
    m->big.wallHeight = 0;
    m->tex.color_n = NULL;
    m->tex.color_s = NULL;
    m->tex.color_e = NULL;
}

void init_2(t_index *m)
{
    m->tex.color_w = NULL;
    m->tex.texX = 0;
	m->tex.texY = 0;
    m->big.side = 0;
    m->tex.step = 0;
	m->tex.texPos = 0;
    m->el.elem = NULL;
    m->el.resolution_line = 0;
    m->el.res_x = 0;
    m->el.res_y = 0;
    m->el.north_line = 0;
    m->el.south_line = 0;
    m->el.west_line = 0;
    m->el.east_line = 0;
    m->el.sprite_line = 0;
    m->el.floor_line = 0;
    m->el.ceilling_line = 0;
    m->el.ceilling_color_r = 0;
    m->el.ceilling_color_g = 0;
    m->el.ceilling_color_b = 0;
	m->el.floor_color_r = 0;
}

void init_3(t_index *m)
{
    m->el.floor_color_g = 0;
    m->el.floor_color_b = 0;
	m->el.c_color_hex = 0;
	m->el.f_color_hex = 0;
	m->el.n_path = NULL;
	m->el.s_path = NULL;
	m->el.w_path = NULL;
	m->el.e_path = NULL;
    m->el.spr_path = NULL;
    m->parse.data = NULL;
    m->parse.map_string = NULL;
    m->parse.map_string_clean = NULL;
    m->parse.map = NULL;
    m->parse.line_nbr = 0;
    m->parse.column_nbr = 0;
    m->parse.pos_x_init = 0;
    m->parse.pos_y_init = 0;
    m->parse.dir = 0;
    m->img.img = NULL;
    m->img.addr = NULL;
    m->img.bits_per_pixel = 0;
}

void init_4(t_index *m)
{
    m->img.line_length = 0;
    m->img.endian = 0;
    m->win.mlx_ptr = NULL;
    m->win.mlx_win = NULL;
    m->tex.color = NULL;
    m->spr.numSprites = 0;
    m->spr.numSprites = 0;
    m->spr.spr_tex = NULL;
	m->spr.sprWidth = 0;
	m->spr.sprHeight = 0;
	m->spr.spriteX = 0;
	m->spr.spriteY = 0;
	m->spr.invDet = 0;
	m->spr.transformX = 0;
	m->spr.transformY = 0;
	m->spr.spriteScreenX = 0;
	m->spr.vMoveScreen = 0;
	m->spr.drawStartY = 0;
}

void init_5(t_index *m)
{
    m->spr.drawEndY = 0;
	m->spr.drawStartX = 0;
	m->spr.drawEndX = 0;
	m->spr.stripe = 0;
	m->spr.texX = 0;
	m->spr.texY = 0;
    m->big.oldDirX = 0;
    m->big.oldPlaneX = 0;
    m->spr.spriteDistance = 0;
}

void create_init(t_index *m)
{
    init_1(m);
    init_2(m);
    init_3(m);
    init_4(m);
    init_5(m);
}
