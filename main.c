/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:06:39 by hbuisser          #+#    #+#             */
/*   Updated: 2020/01/27 19:17:09 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cube3d.h"

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

int ft_close(int keycode, t_struct *window)
{
    if (keycode == MLXK_ESC)
    {
        exit(0);
        window->mlx_win = "";
    }
    return (0);
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

int screen(int screenW, int screenH, int donknowyet, char *title, t_struct *window)
{
    t_image  img;
    
    donknowyet = 1;
    window->mlx_ptr = mlx_init();
    window->mlx_win = mlx_new_window(window->mlx_ptr, screenW, screenH, title);
    mlx_hook(window->mlx_win, 2, 1L<<0, ft_close, &window);
    
    img.img = mlx_new_image(window->mlx_ptr, screenW, screenH);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    my_mlx_pixel_put(&img, 50, 50, 0x00FF0000);
    mlx_put_image_to_window(window->mlx_ptr, window->mlx_win, img.img, 100, 100);
    img.relative_path = "./test.xpm";
    img.img = mlx_xpm_file_to_image(window->mlx_ptr, img.relative_path, &img.img_width, &img.img_height);
    
    return (0);
}

int main()
{
    //position vector of the player
    double posX;
    double posY;
    //direction of the player
    double dirX;
    double dirY;
    //camera plane of the player
    // plane is perpendicular to the direction
    double planeX;
    double planeY;
    // store the time of the current and the previous frame
    // the time difference between these two can be used to determinate how much you should move when a certain key is pressed
    double time;
    double oldTime;
    // x-coordinate on the camera plane that the current x-coordinate of the screen represents
    //the right side of the screen will get coordinate 1
    //the center of the screen gets coordinate 0
    //the left side of the screen gets coordinate -1
    double cameraX;

	double rayDirX;
	double rayDirY;
    int i;
    //current square of the map the ray is in (coordinates of that square)
	int mapX;
	int mapY;
    //distance the ray has to travel from its start position to the first x-side
    //Later in the code their meaning will slightly change.
	double sideDistX;
    double sideDistY;
    //distance the ray has to travel to go from 1 x-side to the next x-side
	double deltaDistX;
    double deltaDistY;
    // length of the ray
    double perpWallDist;
    
	int stepX;
    int stepY;
	int hit; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
    int lineHeight;
    int h;
    int drawStart;
    int drawEnd;
    int color;
    t_struct  window;

    posX = 22;
    posY = 12;
    dirX = -1;
    dirY = 0;
    planeX = 0;
    planeY = 0.66;
    time = 0;
    oldTime = 0;
    i = 0;
    h = 8;
    
    screen(screenWidth, screenHeight, 0, WINDOW_TITLE, &window);
    //The raycasting loop goes through every x, no calculation for every pixel of the screen, only for every vertical stripe
    while(!mlx_loop(window.mlx_ptr))
    {
        while (i < screenWidth)
        {
            //calculate ray position and direction
			cameraX = 2 * i / screenWidth - 1;//x-coordinate in camera space
			rayDirX = dirX + planeX * cameraX;
			rayDirY = dirY + planeY * cameraX;

			hit = 0;
			mapX = posX;
			mapY = posY;
			deltaDistX = fabs(1 / rayDirX);
    		deltaDistY = fabs(1 / rayDirY);
			hit = 0;
            //calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
            //perform DDA
            while (hit == 0)
            {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
                }
                else
                {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
                }
                //Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0)
                perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else 
                perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
            //Calculate height of line to draw on screen
            lineHeight = (int)(h / perpWallDist);
            //calculate lowest and highest pixel to fill in current stripe
            drawStart = -lineHeight / 2 + h / 2;
            if(drawStart < 0)
                drawStart = 0;
            drawEnd = lineHeight / 2 + h / 2;
            if(drawEnd >= h)
                drawEnd = h - 1;
            //give x and y sides different brightness
            if (side == 1)
                color = color / 2;

            //draw the pixels of the stripe as a vertical line
            //verLine(x, drawStart, drawEnd, color);
			i++;
        }
    }
}

/*int main ()
{
    data_t  window;
    t_data  img;

    window.mlx_ptr = mlx_init();
    window.mlx_win = mlx_new_window(window.mlx_ptr, 1000, 500, WINDOW_TITLE);
    img.img = mlx_new_image(window.mlx_ptr, 1000, 500);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    my_mlx_pixel_put(&img, 50, 50, 0x00FF0000);
    mlx_put_image_to_window(window.mlx_ptr, window.mlx_win, img.img, 100, 100);
    //mlx_key_hook(window.mlx_win, close, &window);
    mlx_hook(window.mlx_win, 2, 1L<<0, ft_close, &window);
    // looper avec un hook
    //mlx_loop_hook(mlx, render_next_frame, YourStruct);
    img.relative_path = "./test.xpm";
    img.img = mlx_xpm_file_to_image(window.mlx_ptr, img.relative_path, &img.img_width, &img.img_height);
    mlx_loop(window.mlx_ptr);
}*/