/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/02/08 17:19:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// allowed fct : open, close, read, write, malloc, free, perror, strerror, exit

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void verLine(int i, int drawStart, int drawEnd, int color, t_window *window)
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

void calculate_dist(t_big *big, int side)
{
    if (side == 0)
        big->perpWallDist = (big->mapX - big->posX + (1 - big->stepX) / 2) / big->rayDirX;
    else 
        big->perpWallDist = (big->mapY - big->posY + (1 - big->stepY) / 2) / big->rayDirY;
}

int perform_dda(t_big *big, int hit, t_index *idx)
{
    int side; //was a NS or a EW wall hit?
    
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (big->sideDistX < big->sideDistY)
        {
            big->sideDistX += big->deltaDistX;
            big->mapX += big->stepX;
            side = 0;
        }
        else
        {
            big->sideDistY += big->deltaDistY;
            big->mapY += big->stepY;
            side = 1;
        }
        if (idx->parse->map[big->mapY][big->mapX] > '0') 
            hit = 1;
    }
    return (side);
}

void calculate_step_and_sideDist(t_big *big)
{
    if (big->rayDirX < 0)
    {
        big->stepX = -1;
        big->sideDistX = (big->posX - big->mapX) * big->deltaDistX;
    }
    else
    {
        big->stepX = 1;
        big->sideDistX = (big->mapX + 1.0 - big->posX) * big->deltaDistX;
    }
    if (big->rayDirY < 0)
    {
        big->stepY = -1;
        big->sideDistY = (big->posY - big->mapY) * big->deltaDistY;
    }
    else
    {
        big->stepY = 1;
        big->sideDistY = (big->mapY + 1.0 - big->posY) * big->deltaDistY;
    }
}

void calculate_ray_and_deltaDist(t_big *big, int i, t_index *idx)
{
    //calculate ray position and direction
    big->cameraX = 2 * i / (double)idx->el->resolution_x - 1;//x-coordinate in camera space
    big->rayDirX = big->dirX + big->planeX * big->cameraX;
    big->rayDirY = big->dirY + big->planeY * big->cameraX;
    big->mapX = (int)big->posX;
    big->mapY = (int)big->posY;
    big->deltaDistX = fabs(1 / big->rayDirX);
    big->deltaDistY = fabs(1 / big->rayDirY);
}

void create_algo(t_big *big, t_index *idx)
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
    while (i < idx->el->resolution_x)
    {
        hit = 0;
        calculate_ray_and_deltaDist(big, i, idx);
        calculate_step_and_sideDist(big);
        side = perform_dda(big, hit, idx);
        calculate_dist(big, side);
        lineHeight = (int)(idx->el->resolution_y / big->perpWallDist);
        //calculate lowest and highest pixel to fill in current stripe
        drawStart = -lineHeight / 2 + idx->el->resolution_y / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + idx->el->resolution_y / 2;
        if (drawEnd >= idx->el->resolution_y)
            drawEnd = idx->el->resolution_y - 1;
        //give x and y sides different brightness
        color = 0xffffff;
		if (side == 1)
            color = 0x0000ff;
        verLine(i, drawStart, drawEnd, color, idx->window);
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
    rotSpeed = 0.3;
    oldPlaneX = idx->big->planeX;

    if (keycode == MLXK_ESC)
        exit(0);
    else if (keycode == MLXK_W)
    {
        idx->big->posX += idx->big->dirX * moveSpeed;
        idx->big->posY += idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_S)
    {
        idx->big->posX -= idx->big->posY * moveSpeed;
        idx->big->posY -= idx->big->dirY * moveSpeed;
    }
    else if (keycode == MLXK_A)
    {
        oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(rotSpeed) - idx->big->dirY * sin(rotSpeed);
        idx->big->dirY = oldDirX * sin(rotSpeed) + idx->big->dirY * cos(rotSpeed);
        oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(rotSpeed) - idx->big->planeY * sin(rotSpeed);
        idx->big->planeY = oldPlaneX * sin(rotSpeed) + idx->big->planeY * cos(rotSpeed);
    }
    else if (keycode == MLXK_D)
    {
        oldDirX = idx->big->dirX;
        idx->big->dirX = idx->big->dirX * cos(-rotSpeed) - idx->big->dirY * sin(-rotSpeed);
        idx->big->dirY = oldDirX * sin(-rotSpeed) + idx->big->dirY * cos(-rotSpeed);
        oldPlaneX = idx->big->planeX;
        idx->big->planeX = idx->big->planeX * cos(-rotSpeed) - idx->big->planeY * sin(-rotSpeed);
        idx->big->planeY = oldPlaneX * sin(-rotSpeed) + idx->big->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(idx->window->mlx_ptr, idx->window->mlx_win);
    create_algo(idx->big, idx);
    return (0);
}

void create_settings(t_index *idx)
{
    idx->big->posX = idx->parse->posX;
    idx->big->posY = idx->parse->posY;
    /*if (idx->parse->dir == 'N')
    {
        idx->big->dirX = 0;
        idx->big->dirY = 1;
    }
    else if (idx->parse->dir == 'S')
    {
        idx->big->dirX = 0;
        idx->big->dirY = -1;
    }
    else if (idx->parse->dir == 'W')
    {
        idx->big->dirX = -1;
        idx->big->dirY = 0;
    }
    else if (idx->parse->dir == 'E')
    {
        idx->big->dirX = 1;
        idx->big->dirY = 0;
    }*/
    idx->big->dirX = -1;
    idx->big->dirY = 0;
    idx->big->planeX = 0;
    idx->big->planeY = 0.66;
}

int main(int ac, char **av)
{
    t_index		*idx = malloc(sizeof(t_index));
    t_window	*window = malloc(sizeof(t_window));
    t_image		*img = malloc(sizeof(t_image));
    t_big		*big = malloc(sizeof(t_big));
    t_parse     *parse = malloc(sizeof(t_parse));
    t_elements  *el = malloc(sizeof(t_elements));
    t_color     *color = malloc(sizeof(t_color));

	if (ac < 2)
		return (-1);

    idx->big = big;
    idx->img = img;
    idx->parse = parse;
    idx->el = el;
    idx->window = window;
    color->rgb.r = 1;

	if (parse_cub(idx, av[1]) < 0)
        return (-1);
    window->mlx_ptr = mlx_init();
    window->mlx_win = mlx_new_window(window->mlx_ptr, idx->el->resolution_x, idx->el->resolution_y, WINDOW_TITLE);
    mlx_hook(window->mlx_win, 2, 1L<<1, ft_key, idx);
    //img.img = mlx_new_image(window.mlx_ptr, idx.el->resolution_x, idx.el->resolution_y);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    create_settings(idx);
    create_algo(big, idx);
    //mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, img.img, 0, 0);
    mlx_loop(window->mlx_ptr);
    return (0);
}
