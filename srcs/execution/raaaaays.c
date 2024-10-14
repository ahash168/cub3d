/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/14 21:54:30 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533
#define P2	PI/2
#define P3	3 * PI/2
#define WINDOW_W 1920
#define WINDOW_H 1080
#define MINIMUM 50
#define MAXIMUM 250

int	change_shade(int colour, float dist)
{
	float shade_factor = 0.0;
	if (dist <= MAXIMUM)
		shade_factor = 0.0;;
	if (dist <= MINIMUM)
		shade_factor = 1.0;
	else
		shade_factor = 1.0 - ((dist - MINIMUM) / (MAXIMUM - MINIMUM));
	if(shade_factor < 0.0)
		shade_factor = 0.0;
	if(shade_factor > 1.0)
		shade_factor = 1.0;
	unsigned int trgb = colour; // Replace this with your color
	unsigned char r = (trgb >> 16) & 0xFF;
	unsigned char g = (trgb >> 8) & 0xFF;
	unsigned char b = trgb & 0xFF;
	
	// Apply shading
	r = (unsigned char)(r * shade_factor);
	g = (unsigned char)(g * shade_factor);
	b = (unsigned char)(b * shade_factor);
	
	// Combine back into a TRGB value
	unsigned int shaded_color = (trgb & 0xFF000000) | (r << 16) | (g << 8) | b;
	return (shaded_color);
}

int	shade_floor(int colour, int y, int window_height, int final)
{
	float shade_factor = 0.0;
	float minimum = 50.0;
	
	if (window_height - y < minimum)
		shade_factor = 1.0;
	else if (window_height - y > final)
		shade_factor = 0.0;
	else
		shade_factor = 1.0 - ((y - minimum) / (final - minimum));

	if (shade_factor < 0.0f)
        shade_factor = 0.0f;
    if (shade_factor > 1.0f)
        shade_factor = 1.0f;

	unsigned int trgb = colour;
	unsigned char r = (trgb >> 16) & 0xFF;
	unsigned char g = (trgb >> 8) & 0xFF;
	unsigned char b = trgb & 0xFF;

	r = (unsigned char)(r * shade_factor);
	g = (unsigned char)(g * shade_factor);
	b = (unsigned char)(b * shade_factor);

	unsigned int shaded_color = (trgb & 0xFF000000) | (r << 16) | (g << 8) | b;
	return (shaded_color);
}

void	draw_vertical_line(t_game *game, int x, float h, int window_height, int color)
{
	int	y;

	int i = 0;
	int final;
	y = (window_height - h) / 2;
	while (i < y)
	{
		pixel_put(&game->img, x, i, game->textures.ceiling);
		i++;
	}
	while ((y < window_height - ((window_height - h ) / 2)) && y >= 0)
	{
		pixel_put(&game->img, x, y, color);
		y++;
	}
	final = y;
	while (y < window_height)
	{
		pixel_put(&game->img, x, y, shade_floor(game->textures.floor, y, 1080, final));
		y++;
	}
}

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
		pixel_put(&game->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
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
		if (angle > 0 && angle < PI)
		{
			*inter += 64;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > P2 && angle < P3)) 
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

	y_step = 64;
	x_step = 64 / tan(ray_angle);
	*hy = floor((game->map.player_y * 64) / 64) * 64;
	pixel = inter_check(ray_angle, hy, &y_step, 1);
	*hx = ((game->map.player_x * 64)) + (*hy - ((game->map.player_y * 64))) / tan(ray_angle);
	if ((unit_circle(ray_angle, 'y') && x_step > 0) || (!unit_circle(ray_angle, 'y') && x_step < 0))
		x_step *= -1;
	while (find_wall(*hx, *hy - pixel, game))
	{
		*hx += x_step;
		*hy += y_step;
	}
	return (sqrt(pow(*hx - ((game->map.player_x * 64)), 2) + pow(*hy - ((game->map.player_y * 64)), 2)));
}

int	get_v_inter(t_game *game, float ray_angle, float *vx, float *vy)
{
	float x_step;
	float y_step;
	int pixel;

	x_step = 64;
	y_step = 64 * tan(ray_angle);
	*vx = floor((game->map.player_x * 64) / 64) * 64;
	pixel = inter_check(ray_angle, vx, &x_step, 0);
	*vy = (game->map.player_y * 64) + (*vx - (game->map.player_x * 64)) * tan(ray_angle);
	// printf("first vy: %f\n", tan(ray_angle));
	if ((unit_circle(ray_angle, 'x') && y_step < 0) || (!unit_circle(ray_angle, 'x') && y_step > 0))
		y_step *= -1;
	while (find_wall(*vx - pixel, *vy, game))
	{
		*vx += x_step;
		*vy += y_step;
	}
	// printf("last vy: %f\n", *vy);
	return (sqrt(pow(*vx - (game->map.player_x * 64), 2) + pow(*vy - (game->map.player_y * 64), 2)));
}

void raaaaays(t_game *game)
{
	float fov_rd;
	float h_inter;
	float v_inter;
	float ray;
	float ray_angle;
	float offset;
	float hx;
	float hy;
	float vx;
	float vy;
	fov_rd = 60.00 * DR;
	h_inter = 0.0;
	v_inter = 0.0;
	ray = 0;
	ray_angle = game->map.angle - (fov_rd / 2.00);
	if (ray_angle < 0)
		ray_angle += (2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (2 * PI);
	offset = fov_rd / WINDOW_W;
	float final;
	float no_fishy;
	int colour;
	float pierce = tan(fov_rd / 2.00);
	while (ray < WINDOW_W)
	{
		no_fishy = game->map.angle - ray_angle;
		if (no_fishy < 0)
			no_fishy += (2 * PI);
		else if (no_fishy > (2 * PI))
			no_fishy -= (2 * PI);
		h_inter = get_h_inter(game, ray_angle, &hx, &hy);
		v_inter = get_v_inter(game, ray_angle, &vx, &vy);
		if (v_inter < h_inter)
		{
			final = v_inter * cos(no_fishy);
			colour = 0x9c9358;
			// colour = 0x00b8bfc2;
			// colour *= v_inter / 100;
			colour = change_shade(colour, final);
			// draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), vx, vy, 0x2a9df5);
		}
		else
		{
			final = h_inter * cos(no_fishy);
			colour = 0x9c9358;
			// colour  = 0x002a9df5;
			// colour *= h_inter / 100;
			colour = change_shade(colour, final);
			// draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), hx, hy, 0x2a9df5);
		}
		// float wall_h = (64 * 1080) / final;
		float wall_h = (64 / final) * (960 / pierce);
		if (wall_h > 1080)
			wall_h = 1080;
		draw_vertical_line(game, ray, wall_h, 1080, colour);
		ray++;
		ray_angle += offset;
		if (ray_angle < 0)
			ray_angle += (2 * PI);
		else if (ray_angle > (2 * PI))
			ray_angle -= (2 * PI);
	}
}
