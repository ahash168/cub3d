/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/10 20:52:05 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533
#define P2	PI/2
#define P3	3 * PI/2
#define WINDOW_W 1920
#define WINDOW_H 1080

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		// Draw the current pixel
		pixel_put(&game->img, x0, y0, color);

		// If the line has reached its endpoint, break out of the loop
		if (x0 == x1 && y0 == y1)
			break;

		// Store the error value before changing it
		e2 = 2 * err;

		// Adjust error and move the point horizontally or diagonally
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}

		// Adjust error and move the point vertically or diagonally
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

int unit_circle(float angle, char c) // check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > P2 && angle < P3)
			return (1);
	}
	return (0);
}

int inter_check(float angle, float *inter, float *step, int is_horizon) // check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += 64;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += 64;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int find_wall(float x, float y, t_game *game)
{
	int map_x;
	int map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = floor (x / 64);
	map_y = floor (y / 64);
	if (map_y >= game->map.height || map_x >= game->map.width)
		return (0);
	if (game->map.map[map_y] && map_x <= (int)ft_strlen(game->map.map[map_y]))
		if (game->map.map[map_y][map_x] == '1')
			return (0);
	return (1);
}

int	get_h_inter(t_game *game, float ray_angle, float *hx, float *hy)
{
	float x_step;
	float y_step;
	int pixel;

	x_step = 64;
	y_step = 64 / tan(ray_angle);
	*hy = floor(game->map.player_y * 64);
	// *hy  = (((int)(game->map.player_y * 64) / 64) * 64);
	*hx = (game->map.player_x * 64) + (*hy - (game->map.player_y * 64)) / tan(ray_angle);
	pixel = inter_check(ray_angle, hy, &y_step, 1);
	if ((unit_circle(ray_angle, 'y') && x_step > 0) || (!unit_circle(ray_angle, 'y') && x_step < 0))
		x_step *= -1;
	while (find_wall(*hx, *hy, game))
	{
		*hx += x_step;
		*hy += y_step;
	}
	return (sqrt(pow(*hx - (game->map.player_x * 64), 2) + pow(*hy - (game->map.player_y * 64), 2)));
}

int	get_v_inter(t_game *game, float ray_angle, float *vx, float *vy)
{
	float x_step;
	float y_step;
	int pixel;
	
	x_step = 64;
	y_step = 64 * tan(ray_angle);
	*vx = floor(game->map.player_x * 64);
	// *vx = (((int)(game->map.player_x * 64) / 64) * 64);
	*vy = (game->map.player_y * 64) + (*vx - (game->map.player_x * 64)) * tan(ray_angle);
	pixel = inter_check(ray_angle, vx, &x_step, 1);
	if ((unit_circle(ray_angle, 'y') && x_step > 0) || (!unit_circle(ray_angle, 'y') && x_step < 0))
		x_step *= -1;
	while (find_wall(*vx, *vy, game))
	{
		*vx += x_step;
		*vy += y_step;
	}
	return (sqrt(pow(*vx - (game->map.player_x * 64), 2) + pow(*vy - (game->map.player_y * 64), 2)));
}

void raaaaays(t_game *game)
{
	float fov;
	float h_inter;
	float v_inter;
	float ray;
	float ray_angle;
	float offset;
	float hx = 0;
	float hy = 0;
	float vx = 0;
	float vy = 0;
	
	fov = 60;
	h_inter = 0;
	v_inter = 0;
	ray = 0;
	ray_angle = game->map.angle - (DR * (fov / 2));
	if (ray_angle < 0)
		ray_angle += (2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (2 * PI);
	offset = (DR * fov) / WINDOW_W;
	while (ray < WINDOW_W)
	{
		h_inter = get_h_inter(game, ray_angle, &hx, &hy);
		v_inter = get_v_inter(game, ray_angle, &vx, &vy);
		if (v_inter < h_inter)
		{
			printf("vx: %f	vy: %f\npx: %f	py: %f\n\n\n", vx / 64, vy / 64, game->map.player_x, game->map.player_y);
			draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), vx, vy, 0x2a9df5);
		}
		else
			draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), hx, hy, 0x2a9df5);
		ray_angle += offset;
		if (ray_angle < 0)
			ray_angle += (2 * PI);
		else if (ray_angle > (2 * PI))
			ray_angle -= (2 * PI);
		ray++;
	}
}
