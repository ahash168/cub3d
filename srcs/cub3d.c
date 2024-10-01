/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/01 09:35:33 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	main(int ac, char **av)
// {
// 	t_game	game;

// 	if (ac != 2)
// 		errorer(NULL, 1, USAGE);
// 	parsing(av[1], &game);
// 	// printf("player_x:	%f\nplayer_y:	%f\n", game.map.player_x, game.map.player_y);
// 	game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "cub3d");
// 	rendermap(&game);
// 	mlx_hook(game.window, 2, 0, move_player, &game);
// 	// mlx_hook(game.window, 2, 1L << 0, &keypress, &game);
// 	// mlx_hook(game.window, 17, 1L << 2, &x_button, &game);
// 	mlx_loop(game.mlx);
// 	close_game(&game, 0);
// }


// #include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  (game->map.width * 64)
#define WINDOW_HEIGHT (game->map.height * 64)
#define PI 3.14159265359

// Helper function to draw a pixel
void mlx_pixel_put_safe(t_game *game, void *mlx, void *window, int x, int y, int color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        mlx_pixel_put(mlx, window, x, y, color);
}

// Midpoint Circle Algorithm to draw a circle
void draw_circle(t_game *game, void *mlx, void *window, int x_center, int y_center, int color)
{
    int x = 8;
    int y = 0;
    int decisionOver2 = 1 - x;

    while (y <= x)
    {
        // Draw points in all octants
        mlx_pixel_put_safe(game, mlx, window, x_center + x, y_center + y, color);
        mlx_pixel_put_safe(game, mlx, window, x_center + y, y_center + x, color);
        mlx_pixel_put_safe(game, mlx, window, x_center - x, y_center + y, color);
        mlx_pixel_put_safe(game, mlx, window, x_center - y, y_center + x, color);
        mlx_pixel_put_safe(game, mlx, window, x_center - x, y_center - y, color);
        mlx_pixel_put_safe(game, mlx, window, x_center - y, y_center - x, color);
        mlx_pixel_put_safe(game, mlx, window, x_center + x, y_center - y, color);
        mlx_pixel_put_safe(game, mlx, window, x_center + y, y_center - x, color);
        
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
	printf("%d, %d\n", x_center, y_center);
}

// Draw a line to represent the direction vector
void draw_direction_vector(t_game *game, void *mlx, void *window, int x_center, int y_center, float angle, int color)
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
        mlx_pixel_put_safe(game, mlx, window, x_center, y_center, color);
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

int main(int ac, char **av)
{
    t_game	game;

    if (ac != 2)
        errorer(NULL, 1, USAGE);
    parsing(av[1], &game);
    game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "cub3d");
    int x_pixel = game.map.player_x * 64 + 32;  // Center of the tile
    int y_pixel = game.map.player_y * 64 + 32;  // Center of the tile
    draw_circle(&game, game.mlx, game.window, x_pixel, y_pixel, 0xFFFFFF);  // White circle
    draw_direction_vector(&game, game.mlx, game.window, x_pixel, y_pixel, game.map.angle, 0xFF0000);  // Red vector
    mlx_hook(game.window, 2, 1L << 0, &keypress, &game);
    mlx_loop(game.mlx);
	close_game(&game, 0);
    return (0);
}
