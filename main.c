/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/07 12:27:02 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verline(int i, t_index *m)
{
	int j;
	int k;
	int y;

	j = 0;
	y = m->big.drawStart;
	while (j < y)
	{
		m->img.addr[j * m->el.res_x + i] = m->el.c_color_hex;
		j++;
	}
	while (y < m->big.drawEnd)
	{
		m->tex.texY = (int)m->tex.texPos & (m->tex.texHeight - 1);
		m->tex.texPos += m->tex.step;
		m->img.addr[y * m->el.res_x + i] =
			m->tex.color[m->tex.texY * m->tex.texHeight + m->tex.texX];
		y++;
	}
	k = y;
	while (k < m->el.res_y)
	{
		m->img.addr[k * m->el.res_x + i] = m->el.f_color_hex;
		k++;
	}
}

int		transform_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	create_algo(t_index *m)
{
	int		i;
	int		hit;

	i = 0;
	hit = 0;
	while (i < m->el.res_x)
	{
		hit = 0;
		calculate_ray_and_deltaDist(i, m);
		calculate_step_and_sideDist(m);
		perform_dda(hit, m);
		calculate_dist(m);
		calculate_height_wall(m);
		calculate_textures(m);
		calculate_colors(m);
		verline(i, m);
		m->spr.ZBuffer[i] = m->big.perpWallDist;
		i++;
	}
	sprites_raycasting(m);
	mlx_put_image_to_window(m->win.mlx_ptr, m->win.mlx_win, m->img.img, 0, 0);
}

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
	m->big.rotSpeed = 0.2;
	if (!(m->spr.ZBuffer = malloc(sizeof(float *) * m->el.res_x + 1)))
		return (-1);
	return (1);
}

int		launch_program(t_index *m, char *av)
{
	create_init(m);
	if (parse_cub(m, av) < 0)
		return (-1);
	if (!(m->win.mlx_ptr = mlx_init()))
		return (-1);
	m->win.mlx_win = mlx_new_window
		(m->win.mlx_ptr, m->el.res_x, m->el.res_y, WINDOW_TITLE);
	create_data(m);
	generate_textures(m);
	m->img.img = mlx_new_image(m->win.mlx_ptr, m->el.res_x, m->el.res_y);
	m->img.addr = (int *)mlx_get_data_addr(m->img.img, &m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	create_algo(m);
	return (1);
}

int		main(int ac, char **av)
{
	t_index		m;
    
	if (ac < 2)
		return (-1);
	else if (ac == 2)
	{
		launch_program(&m, av[1]);
		mlx_hook(m.win.mlx_win, 2, 1L << 1, ft_key, &m);
		mlx_hook(m.win.mlx_win, 17, 0, exit_all, &m);
		mlx_loop(m.win.mlx_ptr);
	}
	else if (ac == 3 && !ft_strncmp(av[2], "--save", 5))
	{
		launch_program(&m, av[1]);
		screen_shot(&m);
	}
	return (0);
}
