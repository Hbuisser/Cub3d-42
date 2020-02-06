/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/05 20:36:41 by hbuisser         ###   ########.fr       */
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

# define WINDOW_TITLE "cube3D"
# define MLXK_ESC 53
# define MLXK_W 13
# define MLXK_A 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480

typedef struct		s_window
{
    void		*mlx_ptr;
    void		*mlx_win;
    int			mlx_height;
    int			mlx_weight;
}					t_window;

typedef struct		s_image
{
    void        *img;
    char        *relative_path;
    int         img_width;
    int         img_height;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}					t_image;

typedef struct      s_vector
{
    double x;
    double y;
}                   t_vector;

typedef union 
{
	unsigned int 	hexcode;
	struct
	{
		unsigned char	r;
		unsigned char 	g;
		unsigned char 	b;
	}				rgb;
}					t_color;

typedef struct      s_parse
{
    char    *data;
    char    *map_string;
    char    *map_string_clean;
    char	**map;
    int     line_nbr;
    int     column_nbr;
    char    dir;
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
    t_color	ceilling_color;
	t_color	floor_color;
	char 	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
    char    *spr_path;
}                   t_elements;

typedef struct      s_big
{
    double		posX;
    double		posY;
    double		dirX;
    double		dirY;
    double		planeX;
    double		planeY;
    double		cameraX;
    double		rayDirX;
	double		rayDirY;
    int			mapX;
	int			mapY;
	double		sideDistX;
    double		sideDistY;
	double		deltaDistX;
    double		deltaDistY;
	double		perpWallDist;
	int			stepX;
    int			stepY;
}					t_big;

typedef struct 		s_index
{
	t_window    *window;
	t_image     *img;
	t_big       *big;
    t_parse     *parse;
    t_elements  *el;
}					t_index;

/*
** Main file
*/

void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	verLine(int i, int drawStart, int drawEnd, int color, t_window *window);
int		perform_dda(t_big *play, int hit);
void	calculate_step_and_sideDist(t_big *big);
void	calculate_ray_and_deltaDist(t_big *big, int i);
void	calculate_dist(t_big *big, int side);
void	create_algo(t_big *big, t_window *window);
int		ft_key(int keycode, t_index *idx);
void	create_settings(t_big *big);

/*
** Parsing
*/

int		parse_cub(t_index *idx, char *filename);

/*
** Map and elements errors
*/

int		check_errors(t_index *idx);
int     check_elements_errors(t_index *idx);

/*
** Parse elements
*/

int     create_elements(t_index *idx);

/*
** Get textures elements
*/

char *get_east_texture(t_index *idx);
char *get_west_texture(t_index *idx);
char *get_south_texture(t_index *idx);
char *get_north_texture(t_index *idx);
char *get_sprite_texture(t_index *idx);

/*
** GNL
*/

int		get_next_line(const int fd, char **line);

#endif