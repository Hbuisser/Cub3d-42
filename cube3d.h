/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:24 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/01 13:41:45 by hbuisser         ###   ########.fr       */
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

#endif
