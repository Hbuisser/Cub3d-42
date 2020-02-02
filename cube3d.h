/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/02 15:37:45 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

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

# define TRUE 1
# define FALSE 0

# define SQUARE(x) ((x) * (x))

# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480

typedef struct		s_struct
{
    //t_bool		running;
    void		*mlx_ptr;
    void		*mlx_win;
    int			mlx_height;
    int			mlx_weight;
}					t_struct;

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

typedef struct      s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double cameraX;
    double rayDirX;
	double rayDirY;
    int mapX;
	int mapY;
	double sideDistX;
    double sideDistY;
	double deltaDistX;
    double deltaDistY;
	double perpWallDist;
	int stepX;
    int stepY;
}					t_player;

typedef struct 		s_index
{
	t_struct *window;
	t_image *img;
	t_player *play;
}					t_index;

int	create_trgb(int t, int r, int g, int b);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
void verLine(int i, int drawStart, int drawEnd, int color, t_struct *window);
int perform_dda(t_player *play, int hit);
void calculate_step_and_sideDist(t_player *play);
void calculate_ray_and_deltaDist(t_player *play, int i);
void calculate_dist(t_player *play, int side);
void create_algo(t_player *play, t_struct *window);
int ft_key(int keycode, t_index *idx);
void create_settings(t_player *play);

#endif
