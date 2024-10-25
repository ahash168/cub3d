/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/25 14:02:14 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533

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

void	door_str(t_game *game)
{
	int	x;
	int	y;
	float	angle;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	angle = game->map.angle;
	// printf("%d, %d, %f\n", x, y, angle);
	if (((angle <= 135 * DR && angle > 45 * DR) && game->map.map[y + 1][x] == 'D')
		|| ((angle <= 255 * DR && angle > 135 * DR) && game->map.map[y][x - 1] == 'D')
		|| ((angle <= 255 * DR && angle > 315 * DR) && game->map.map[y - 1][x] == 'D')
		|| (((angle <= 315 * DR && angle > 360 * DR) || (angle <= 45 * DR && angle > 0 * DR)) && game->map.map[y][x + 1] == 'D'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, "OPEN DOORRRR");
	else if (((angle <= 135 * DR && angle > 45 * DR) && game->map.map[y + 1][x] == 'O')
		|| ((angle <= 255 * DR && angle > 135 * DR) && game->map.map[y][x - 1] == 'O')
		|| ((angle <= 255 * DR && angle > 315 * DR) && game->map.map[y - 1][x] == 'O')
		|| (((angle <= 315 * DR && angle > 360 * DR) || (angle <= 45 * DR && angle > 0 * DR)) && game->map.map[y][x + 1] == 'O'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, "CLOSE DOORRRR");
}

void	rendermap(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	// draw_map(game);
	// draw_player(game, game->map.player_x * 64, game->map.player_y * 64, 0x2a9df5);
    raaaaays(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	door_str(game);
	mlx_destroy_image(game->mlx, game->img.img);
}
