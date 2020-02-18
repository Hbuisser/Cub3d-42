/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/17 21:48:20 by hbuisser         ###   ########.fr       */
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

#define uDiv 1
#define vDiv 1
#define vMove 0

typedef struct		s_window
{
    void		*mlx_ptr;
    void		*mlx_win;
}					t_window;

typedef struct		s_image
{
    void        *img;
    int         *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}					t_image;

typedef struct      s_parse
{
    char	*data;
    char	*map_string;
    char	*map_string_clean;
    char 	**map;
    int		line_nbr;
    int		column_nbr;
    float	pos_x_init;
    float	pos_y_init;
    char	dir;
}                   t_parse;

typedef struct      s_elements
{
    char	**elem;
    int		resolution_line;
    int		resolution_x;
    int		resolution_y;
    int 	north_line;
    int 	south_line;
    int 	west_line;
    int 	east_line;
    int 	sprite_line;
    int		floor_line;
    int		ceilling_line;
    int 	ceilling_color_r;
    int 	ceilling_color_g;
    int 	ceilling_color_b;
	int 	floor_color_r;
    int 	floor_color_g;
    int 	floor_color_b;
	int		c_color_hex;
	int		f_color_hex;
	char 	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
    char    *spr_path;
}                   t_elements;

typedef struct      s_big
{
    float		posX;
    float		posY;
    float		dirX;
    float		dirY;
    float		planeX;
    float		planeY;
    float		cameraX;
    float		rayDirX;
	float		rayDirY;
    int			mapX;
	int			mapY;
	float		sideDistX;
    float		sideDistY;
	float		deltaDistX;
    float		deltaDistY;
	float		perpWallDist;
	int			stepX;
    int			stepY;
    int         drawStart;
    int         drawEnd;
    int         wallHeight;
    int         lineHeight;
    int         side;
}					t_big;

typedef struct      s_tex
{
    int         texWidth;
    int         texHeight;
    void        *color_n;
    void        *color_s;
    void        *color_e;
    void        *color_w;
    int		    texX;
	int 	    texY;
    float	    step;
	float 	    texPos;
    int         *color;
}                   t_tex;

typedef struct      s_spr
{
    int         numSprites;
    int         x;
    int         y;
	void		*spr_tex;
    int         *color;
	int 		sprWidth;
	int 		sprHeight;
	float 		spriteX;
	float		spriteY;
    float		invDet;
	float		transformX;
	float		transformY;
	int 		spriteScreenX;
	int 		vMoveScreen;
	int 		drawStartY;
	int 		drawEndY;
	int 		drawStartX;
	int 		drawEndX;
	int 		stripe;
	int 		texX;
	int 		texY;
    double      *ZBuffer;
}                   t_spr;

typedef struct 		s_index
{
	t_window    *window;
	t_image     *img;
	t_big       *big;
    t_parse     *parse;
    t_elements  *el;
    t_tex       *tex;
    t_spr       *spr;
}					t_index;

/*
** Main file
*/

void    create_algo(t_index *idx);
int 	transform_to_hex(int r, int g, int b);

/*
** Initialisation
*/

void    create_init(t_index *idx);

/*
** Parsing
*/

int		parse_cub(t_index *idx, char *filename);

/*
** Map and elements errors
*/

int		check_map_errors(t_index *idx, char *map_string_clean);
int     check_elements_errors(t_index *idx);

/*
** Parse elements
*/

int     create_elements(t_index *idx);

/*
** Get textures elements
*/

char	*get_east_texture(t_index *idx);
char	*get_west_texture(t_index *idx);
char	*get_south_texture(t_index *idx);
char	*get_north_texture(t_index *idx);
char	*get_sprite_texture(t_index *idx);

/*
** Main algo
*/

void    calculate_ray_and_deltaDist(int i, t_index *idx);
void    calculate_step_and_sideDist(t_index *idx);
void    perform_dda(int hit, t_index *idx);
void    calculate_dist(t_index *idx);
void    calculate_height_wall(t_index *idx);

/*
** Keycode
*/

int     ft_key(int keycode, t_index *idx);

/*
** Textures
*/

int     generate_textures(t_index *idx);
void	calculate_textures(t_index *idx);
void    calculate_colors(t_index *idx);

/*
**  Sprites
*/

void sprites_raycasting(t_index *idx);

/*
** GNL
*/

int		get_next_line(const int fd, char **line);
char	**ft_strsplit(const char *s, char c);

#endif
