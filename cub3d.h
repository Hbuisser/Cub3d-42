/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/03/08 14:19:24 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./miniLibX/mlx.h"

# define WINDOW_TITLE "cub3D"
# define MLXK_ESC 53
# define MLXK_X 17
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124
# define MLXK_UP 126
# define MLXK_DOWN 125
# define MLXK_TD 14
# define MLXK_TG 12

# define uDiv 2
# define vDiv 2
# define vMove 0

typedef struct		s_win
{
	void	*mlx_ptr;
	void	*mlx_win;
}					t_win;

typedef struct		s_image
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_image;

typedef struct		s_parse
{
	char	*data;
	char	*map_string;
	char	*map_string_clean;
	char	**map;
	int		line_nbr;
	int		column_nbr;
	float	pos_x_init;
	float	pos_y_init;
	char	dir;
}					t_parse;

typedef struct		s_elements
{
	char	**elem;
	int		resolution_line;
	int		res_x;
	int		res_y;
	int		north_line;
	int		south_line;
	int		west_line;
	int		east_line;
	int		sprite_line;
	int		floor_line;
	int		ceilling_line;
	int		ceilling_color_r;
	int		ceilling_color_g;
	int		ceilling_color_b;
	int		floor_color_r;
	int		floor_color_g;
	int		floor_color_b;
	int		c_color_hex;
	int		f_color_hex;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	char	*spr_path;
}					t_elements;

typedef struct		s_big
{
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	cameraX;
	float	rayDirX;
	float	rayDirY;
	int		mapX;
	int		mapY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	float	perpWallDist;
	int		stepX;
	int		stepY;
	int		drawStart;
	int		drawEnd;
	int		wallHeight;
	int		lineHeight;
	int		side;
	float	moveSpeed;
	float	oldDirX;
	float	rotSpeed;
	float	oldPlaneX;
}					t_big;

typedef struct		s_tex
{
	int		texWidth;
	int		texHeight;
	void	*color_n;
	void	*color_s;
	void	*color_e;
	void	*color_w;
	int		texX;
	int		texY;
	float	step;
	float	texPos;
	int		*color;
}					t_tex;

typedef struct		s_spr
{
	int		numSprites;
	void	*spr_tex;
	int		*color;
	int		sprWidth;
	int		sprHeight;
	float	spriteX;
	float	spriteY;
	float	invDet;
	float	transformX;
	float	transformY;
	int		spriteScreenX;
	int		vMoveScreen;
	int		drawStartY;
	int		drawEndY;
	int		drawStartX;
	int		drawEndX;
	int		stripe;
	int		texX;
	int		texY;
	float	*ZBuffer;
	int		*sprites_x;
	int		*sprites_y;
	float	spriteDistance;
}					t_spr;

typedef struct		s_index
{
	t_win		win;
	t_image		img;
	t_big		big;
	t_parse		parse;
	t_elements	el;
	t_tex		tex;
	t_spr		spr;
}					t_index;

void	create_algo(t_index *m);
int		transform_to_hex(int r, int g, int b);
void	create_init(t_index *m);

void	init_5(t_index *m);
void	init_4(t_index *m);
void	init_3(t_index *m);
void	init_2(t_index *m);
void	init_1(t_index *m);

int		create_data(t_index *m);
int		parse_cub(t_index *m, char *filename);
int		check_map_errors(t_index *m);
int		check_elements_errors(t_index *m);
int		new_strlen(char *s);
int		check_borders_lines(t_index *m);
int		check_borders_columns(t_index *m);
int     create_elements(t_index *m);
int		check_dir_letter(t_index *m);

char	*get_east_texture(t_index *m);
char	*get_west_texture(t_index *m);
char	*get_south_texture(t_index *m);
char	*get_north_texture(t_index *m);
char	*get_sprite_texture(t_index *m);

void    calculate_ray_and_deltadist(int i, t_index *m);
void    calculate_step_and_sidedist(t_index *m);
void    perform_dda(int hit, t_index *m);
void    calculate_dist(t_index *m);
void    calculate_height_wall(t_index *m);
int     ft_key(int keycode, t_index *m);
int		exit_all(t_index *m);
int     generate_textures(t_index *m);
void	calculate_textures(t_index *m);
void    calculate_colors(t_index *m);
void	sprites_raycasting(t_index *m);
void	verline_sprites(t_index *m);
int		free_all(t_index *m, int ret);
int		get_next_line(const int fd, char **line);
char	**ft_strsplit(const char *s, char c);
int		screen_shot(t_index *m);

#endif
