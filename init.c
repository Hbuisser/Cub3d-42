/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:25:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 19:39:26 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_1(t_index *m)
{
	m->big.camerax = 0;
	m->big.mapx = 0;
	m->big.raydiry = 0;
	m->big.raydirx = 0;
	m->big.mapx = 0;
	m->big.mapy = 0;
	m->big.sidedistx = 0;
	m->big.sidedisty = 0;
	m->big.deltadistx = 0;
	m->big.deltadisty = 0;
	m->big.perpwalldist = 0;
	m->big.stepx = 0;
	m->big.stepy = 0;
	m->big.drawstart = 0;
	m->big.drawend = 0;
	m->big.lineheight = 0;
	m->big.wallheight = 0;
	m->tex.color_n = NULL;
	m->tex.color_s = NULL;
	m->tex.color_e = NULL;
}

void	init_2(t_index *m)
{
	m->tex.color_w = NULL;
	m->tex.texx = 0;
	m->tex.texy = 0;
	m->big.side = 0;
	m->tex.step = 0;
	m->tex.texpos = 0;
	m->el.elem = NULL;
	m->el.resolution_line = 0;
	m->el.res_x = 0;
	m->el.res_y = 0;
	m->el.north_line = 0;
	m->el.south_line = 0;
	m->el.west_line = 0;
	m->el.east_line = 0;
	m->el.sprite_line = 0;
	m->el.f_l = 0;
	m->el.c_l = 0;
	m->el.c_r = 0;
	m->el.c_g = 0;
	m->el.c_b = 0;
	m->el.f_r = 0;
}

void	init_3(t_index *m)
{
	m->el.f_g = 0;
	m->el.f_b = 0;
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

void	init_4(t_index *m)
{
	m->img.line_length = 0;
	m->img.endian = 0;
	m->win.mlx_ptr = NULL;
	m->win.mlx_win = NULL;
	m->tex.color = NULL;
	m->spr.numsprites = 0;
	m->spr.numsprites = 0;
	m->spr.spr_tex = NULL;
	m->spr.sprwidth = 0;
	m->spr.sprheight = 0;
	m->spr.spritex = 0;
	m->spr.spritey = 0;
	m->spr.invdet = 0;
	m->spr.transformx = 0;
	m->spr.transformy = 0;
	m->spr.spritescreenx = 0;
	m->spr.vmovescreen = 0;
	m->spr.drawstarty = 0;
}

void	init_5(t_index *m)
{
	m->spr.drawendy = 0;
	m->spr.drawstartx = 0;
	m->spr.drawendx = 0;
	m->spr.stripe = 0;
	m->spr.texx = 0;
	m->spr.texy = 0;
	m->big.olddirx = 0;
	m->big.oldplanex = 0;
	m->spr.spritedistance = 0;
}
