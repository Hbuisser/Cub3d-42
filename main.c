/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/02 15:29:53 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// allowed fct : open, close, read, write, malloc, free, perror, strerror, exit

int	create_trgb(int t, int r, int g, int b)
{
	return(b << 24 | g << 16 | r << 8 | t);
}


void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void verLine(int i, int drawStart, int drawEnd, int color, t_struct *window)
{
    int y;

    y = drawStart;
    while (y < drawEnd)
    {
        //my_mlx_pixel_put(img, drawEnd, drawStart, color);
        mlx_pixel_put(window->mlx_ptr, window->mlx_win, i, y, color);
        y++;
    }
}

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int perform_dda(t_player *play, int hit)
{
    int side; //was a NS or a EW wall hit?

    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (play->sideDistX < play->sideDistY)
        {
            play->sideDistX += play->deltaDistX;
            play->mapX += play->stepX;
            side = 0;
        }
        else
        {
            play->sideDistY += play->deltaDistY;
            play->mapY += play->stepY;
            side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[play->mapX][play->mapY] > 0) 
            hit = 1;
    }
    return (side);
}

void calculate_step_and_sideDist(t_player *play)
{
    if (play->rayDirX < 0)
    {
        play->stepX = -1;
        play->sideDistX = (play->posX - play->mapX) * play->deltaDistX;
    }
    else
    {
        play->stepX = 1;
        play->sideDistX = (play->mapX + 1.0 - play->posX) * play->deltaDistX;
    }
    if (play->rayDirY < 0)
    {
        play->stepY = -1;
        play->sideDistY = (play->posY - play->mapY) * play->deltaDistY;
    }
    else
    {
        play->stepY = 1;
        play->sideDistY = (play->mapY + 1.0 - play->posY) * play->deltaDistY;
    }
}

void calculate_ray_and_deltaDist(t_player *play, int i)
{
    //calculate ray position and direction
    play->cameraX = 2 * i / (double)screenWidth - 1;//x-coordinate in camera space
    play->rayDirX = play->dirX + play->planeX * play->cameraX;
    play->rayDirY = play->dirY + play->planeY * play->cameraX;
    play->mapX = (int)play->posX;
    play->mapY = (int)play->posY;
    play->deltaDistX = fabs(1 / play->rayDirX);
    play->deltaDistY = fabs(1 / play->rayDirY);
}

void calculate_dist(t_player *play, int side)
{
    if (side == 0)
        play->perpWallDist = (play->mapX - play->posX + (1 - play->stepX) / 2) / play->rayDirX;
    else 
        play->perpWallDist = (play->mapY - play->posY + (1 - play->stepY) / 2) / play->rayDirY;
}

void create_algo(t_player *play, t_struct *window)
{
    int i;
    int hit; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;

    i = 0;
    hit = 0;
    while (i < screenWidth)
    {
        hit = 0;
        calculate_ray_and_deltaDist(play, i);
        calculate_step_and_sideDist(play);
        side = perform_dda(play, hit);
        calculate_dist(play, side);
        lineHeight = (int)(screenHeight / play->perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;
        //give x and y sides different brightness
        color = 0xffffff;
		if (side == 1)
            color = 0x0000ff;
        verLine(i, drawStart, drawEnd, color, window);
        i++;
    }
}

int ft_key(int keycode, t_index *idx)
{
    double moveSpeed;
    double oldDirX;
    double rotSpeed;
    double oldPlaneX;

    moveSpeed = 1;
    rotSpeed = 0.2;
    oldPlaneX = idx->play->planeX;
    if (keycode == MLXK_ESC)
        exit(0);
    else if (keycode == MLXK_W)
    {
        idx->play->posX += idx->play->dirX * moveSpeed;
        idx->play->posY += idx->play->dirY * moveSpeed;
    }
    else if (keycode == MLXK_S)
    {
        idx->play->posX -= idx->play->dirX * moveSpeed;
        idx->play->posY -= idx->play->dirY * moveSpeed;
    }
    else if (keycode == MLXK_A)
    {
        oldDirX = idx->play->dirX;
        idx->play->dirX = idx->play->dirX * cos(rotSpeed) - idx->play->dirY * sin(rotSpeed);
        idx->play->dirY = oldDirX * sin(rotSpeed) + idx->play->dirY * cos(rotSpeed);
        oldPlaneX = idx->play->planeX;
        idx->play->planeX = idx->play->planeX * cos(rotSpeed) - idx->play->planeY * sin(rotSpeed);
        idx->play->planeY = oldPlaneX * sin(rotSpeed) + idx->play->planeY * cos(rotSpeed);
    }
    else if (keycode == MLXK_D)
    {
        oldDirX = idx->play->dirX;
        idx->play->dirX = idx->play->dirX * cos(-rotSpeed) - idx->play->dirY * sin(-rotSpeed);
        idx->play->dirY = oldDirX * sin(-rotSpeed) + idx->play->dirY * cos(-rotSpeed);
        oldPlaneX = idx->play->planeX;
        idx->play->planeX = idx->play->planeX * cos(-rotSpeed) - idx->play->planeY * sin(-rotSpeed);
        idx->play->planeY = oldPlaneX * sin(-rotSpeed) + idx->play->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(idx->window->mlx_ptr, idx->window->mlx_win);
    create_algo(idx->play, idx->window);
    return (0);
}

void create_settings(t_player *play)
{
    play->posX = 22;
    play->posY = 12;
    play->dirX = -1;
    play->dirY = 0;
    play->planeX = 0;
    play->planeY = 0.66;
}

int main()
{
    t_index  idx;
    t_struct  window;
    t_image   img;
    t_player  play;

    idx.window = &window;
    idx.play = &play;
    idx.img = &img;
    
    window.mlx_ptr = mlx_init();
    window.mlx_win = mlx_new_window(window.mlx_ptr, screenWidth, screenHeight, WINDOW_TITLE);
    mlx_hook(window.mlx_win, 2, 1L<<0, ft_key, &idx);
    img.img = mlx_new_image(window.mlx_ptr, screenWidth, screenHeight);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    create_settings(&play);
    create_algo(&play, &window);
    //mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, img.img, 0, 0);
    mlx_loop(window.mlx_ptr);
    return (0);
}
