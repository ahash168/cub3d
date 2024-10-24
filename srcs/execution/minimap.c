/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/24 19:30:08 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_circle(t_game *game, int x_center, int y_center, int color)
{
    int x = 8;
    int y = 0;
    int decisionOver2 = 1 - x;

    while (y <= x)
    {
        pixel_put(&game->img, x_center + x, y_center + y, color);
        pixel_put(&game->img, x_center + y, y_center + x, color);
        pixel_put(&game->img, x_center - x, y_center + y, color);
        pixel_put(&game->img, x_center - y, y_center + x, color);
        pixel_put(&game->img, x_center - x, y_center - y, color);
        pixel_put(&game->img, x_center - y, y_center - x, color);
        pixel_put(&game->img, x_center + x, y_center - y, color);
        pixel_put(&game->img, x_center + y, y_center - x, color);
        
        y++;
        if (decisionOver2 <= 0)
        {
            decisionOver2 += 2 * y + 1;
        }
        else
        {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

// Draw a line to represent the direction vector
void draw_direction_vector(t_game *game, int x_center, int y_center, float angle, int color)
{
    // Use angle to calculate the endpoint of the line
    int x_end = x_center + cos(angle) * 10;
    int y_end = y_center + sin(angle) * 10;

    // Draw a simple line using Bresenham's algorithm
    int dx = abs(x_end - x_center);
    int dy = abs(y_end - y_center);
    int sx = (x_center < x_end) ? 1 : -1;
    int sy = (y_center < y_end) ? 1 : -1;
    int err = dx - dy;
    
    while (x_center != x_end || y_center != y_end)
    {
        pixel_put(&game->img, x_center, y_center, color);
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x_center += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y_center += sy;
        }
    }
}

void	draw_player(t_game *game, int x, int y, int colour)
{
	draw_circle(game, x, y, colour);
	draw_direction_vector(game, x, y, game->map.angle, colour);
}

void	draw_wall(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y;
	while (++i < y + 63)
	{
		j = x - 1;
		while (++j < x + 63)
			pixel_put(&game->img, j, i, colour);
	}
}

void	draw_floor(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y;
	while (++i < y + 63)
	{
		j = x - 1;
		if (i == y + 1 || i == y + 62)
			while (++j < x + 63)
				pixel_put(&game->img, j, i, colour);
		else
		{
			pixel_put(&game->img, j + 1, i, colour);
			pixel_put(&game->img, j + 62, i, colour);
		}
	}
}

void	draw_map(t_game *game)
{
	int i = -1;
	int j;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == '1')
				draw_wall(game, j * 64, i * 64, 0xb8bfc2);
			else if (game->map.map[i][j] == ' ')
				draw_wall(game, j * 64, i * 64, 0x242424);
			else
				draw_floor(game, j * 64, i * 64, 0xf7adbc);
		}
	}	
}
//
void	rendermap(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	// draw_map(game);
	// draw_player(game, game->map.player_x * 64, game->map.player_y * 64, 0x2a9df5);
    raaaaays(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
}

