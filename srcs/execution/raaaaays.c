/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/24 20:17:09 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533f
#define P2	PI/2.f
#define P3	3.f * PI/2
#define WINDOW_W 1920
#define WINDOW_H 1080
#define MINIMUM 50
#define MAXIMUM 350


int	change_shade(int colour, float dist, float avg)
{
	float shade_factor = (dist <= MINIMUM) * 1.f + (dist >= MAXIMUM) * 0.f;
	// if (dist >= MAXIMUM)
	// 	shade_factor = 0.0;
	// if (dist <= MINIMUM)
	// 	shade_factor = 1.0;
	if (dist > MINIMUM && dist < MAXIMUM)
	{
		shade_factor = avg; // cacheable
		if(shade_factor < 0.0f)
			shade_factor = 0.0f;
		if(shade_factor > 1.0f)
			shade_factor = 1.0f;
	}
	unsigned int trgb = colour; // Replace this with your color
	unsigned char r = ((trgb >> 16) & 0xFF) * shade_factor;
	unsigned char g = ((trgb >> 8) & 0xFF) * shade_factor;
	unsigned char b = (trgb & 0xFF) * shade_factor;

	// r = (unsigned char)(r * shade_factor);
	// g = (unsigned char)(g * shade_factor);
	// b = (unsigned char)(b * shade_factor);

	unsigned int shaded_color = (trgb & 0xFF000000) | (r << 16) | (g << 8) | b;
	return (shaded_color);
}

int	shade_floor(int colour, int y, int window_height, int final)
{
	float shade_factor = 1.f;
	const float minimum = 50.0;
	const float maximum = 350.0;

	(void)final;
	int cached_check = window_height - y;
	if (cached_check <= minimum)
		shade_factor = 1.f;
	else if (cached_check >= maximum)
		shade_factor = 0.f;
	else
	{
		shade_factor = 1.f - (((cached_check) - minimum) / (maximum - minimum));
		if (shade_factor < 0.f)
    	    shade_factor = 0.f;
    	if (shade_factor > 1.f)
    	    shade_factor = 1.f;
	}

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

// void	draw_vertical_line(t_game *game, int x, float h, int window_height, int color, float finale)
// {
// 	int	y;
// 	(void)finale;
// 	int i = 0;
// 	int final;
// 	y = (window_height - h) / 2;
// 	while (i < y)
// 	{
// 		pixel_put(&game->img, x, i, game->textures.ceiling);
// 		i++;
// 	}
// 	while ((y < window_height - ((window_height - h ) / 2)) && y >= 0)
// 	{
// 		pixel_put(&game->img, x, y, color);
// 		y++;
// 	}
// 	final = y;
// 	while (y < window_height)
// 	{

// 		int clr = shade_floor(game->textures.floor, y, 1080, finale);
// 		// int clr = 0x000000;
// 		pixel_put(&game->img, x, y, clr);
// 		y++;
// 	}
// }

int get_pixel_color_from_texture(t_data *texture, int x, int y)
{
    char *pixel;
    int color;

    pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

void	draw_vertical_line(t_game *game, int x, float h, int window_height, float distance, t_data *texture, float huh)
{
	int	y = 0;
	int i = 0;
	int tex_x, tex_y;
	int tex_height = 256; // Assuming all walls have the same height
	int tex_width = 256;   // Assuming all walls have the same width
	int final;
	float dist_max_min_avg = 1.f - ((distance - MINIMUM) / (MAXIMUM - MINIMUM));

	// tex_x = (int)huh * (tex_width / 64);
	// tex_x = (int)((int)(huh * 4) % tex_width);  // Calculate the X coordinate in the texture
	tex_x = (int)(huh * (tex_width / 64));
	if (tex_x >= tex_width)  // Wrap the value within the texture width
    	tex_x = tex_x - (tex_x / tex_width) * tex_width;


	if (h < window_height)
	{
		float half_height = (window_height - h) / 2.f; //
		float factor2 = tex_height / h;
		y = (window_height - h) / 2;
		while (i < y)
		{
			pixel_put(&game->img, x, i, game->textures.ceiling);
			i++;
		}
		while (y < window_height - half_height && y >= 0)
		{
			tex_y = (int)((y - half_height) * factor2);
			int color = get_pixel_color_from_texture(texture, tex_x, tex_y);
			color = change_shade(color, distance, dist_max_min_avg); //
			pixel_put(&game->img, x, y, color);
			y++;
		}
		final = y;
		while (y < window_height)
		{
			int clr = shade_floor(game->textures.floor, y, window_height, distance); //
			pixel_put(&game->img, x, y, clr);
			// pixel_put(&game->img, x, y, game->textures.floor);
			y++;
		}
	}
	else if (h > window_height)
	{
		float factor = tex_height / h;
		int start = ((int)h - window_height) / 2;
		int temp  = start;
		y = 0;
		while ((start < h - temp) && y >= 0 && y < window_height)
		{
			tex_y = (int)(start * factor);
			int color = get_pixel_color_from_texture(texture, tex_x, tex_y);
			color = change_shade(color, distance, dist_max_min_avg); //
			pixel_put(&game->img, x, y, color);
			start++;
			y++;
		}
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

// void raaaaays(t_game *game)
// {
// 	float fov_rd;
// 	float h_inter;
// 	float v_inter;
// 	float ray;
// 	float ray_angle;
// 	float offset;
// 	float hx;
// 	float hy;
// 	float vx;
// 	float vy;
// 	fov_rd = 60.00 * DR;
// 	h_inter = 0.0;
// 	v_inter = 0.0;
// 	ray = 0;
// 	ray_angle = game->map.angle - (fov_rd / 2.00);
// 	if (ray_angle < 0)
// 		ray_angle += (2 * PI);
// 	else if (ray_angle > (2 * PI))
// 		ray_angle -= (2 * PI);
// 	offset = fov_rd / WINDOW_W;
// 	float final;
// 	float no_fishy;
// 	int colour;
// 	float pierce = tan(fov_rd / 2.00);
// 	while (ray < WINDOW_W)
// 	{
// 		no_fishy = game->map.angle - ray_angle;
// 		if (no_fishy < 0)
// 			no_fishy += (2 * PI);
// 		else if (no_fishy > (2 * PI))
// 			no_fishy -= (2 * PI);
// 		h_inter = get_h_inter(game, ray_angle, &hx, &hy);
// 		v_inter = get_v_inter(game, ray_angle, &vx, &vy);
// 		if (v_inter < h_inter)
// 		{
// 			final = v_inter * cos(no_fishy);
// 			// colour = 0x9c9358;
// 			colour = 0x00b8bfc2;
// 			colour *= v_inter / 100;
// 			colour = change_shade(colour, final);
// 			// draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), vx, vy, 0x2a9df5);
// 		}
// 		else
// 		{
// 			final = h_inter * cos(no_fishy);
// 			// colour = 0x9c9358;
// 			colour  = 0x002a9df5;
// 			colour *= h_inter / 100;
// 			colour = change_shade(colour, final);
// 			// draw_line(game, (game->map.player_x * 64), (game->map.player_y * 64), hx, hy, 0x2a9df5);
// 		}
// 		// float wall_h = (64 * 1080) / final;
// 		float wall_h = (64 / final) * (960 / pierce);
// 		if (wall_h > 1080)
// 			wall_h = 1080;
// 		draw_vertical_line(game, ray, wall_h, 1080, colour, final);
// 		ray++;
// 		ray_angle += offset;
// 		if (ray_angle < 0)
// 			ray_angle += (2 * PI);
// 		else if (ray_angle > (2 * PI))
// 			ray_angle -= (2 * PI);
// 	}
// }


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
	fov_rd = 60.0f * DR;
	h_inter = 0.0f;
	v_inter = 0.0f;
	ray = 0;
	ray_angle = game->map.angle - (fov_rd / 2.f);
	if (ray_angle < 0)
		ray_angle += (2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (2 * PI);
	offset = fov_rd / WINDOW_W;
	float final;
	float no_fishy;
	// int colour;
	float pierce = tanf(fov_rd / 2.f);
	// int clrrr = 0x23fcde;
	// printf("%x\n\n", clrrr);
	t_data *current_texture; // Holds the texture for the current wall
	
	while (ray < WINDOW_W)
	{
		no_fishy = game->map.angle - ray_angle;
		if (no_fishy < 0)
			no_fishy += (2 * PI);
		else if (no_fishy > (2 * PI))
			no_fishy -= (2 * PI);
		h_inter = get_h_inter(game, ray_angle, &hx, &hy);
		v_inter = get_v_inter(game, ray_angle, &vx, &vy);
		float intercept = 0;
		if (v_inter < h_inter)
		{
			intercept = vy;
			final = v_inter * cosf(no_fishy);
			current_texture = &game->textures.texture[W_N]; // Use east texture for vertical walls
		}
		else
		{
			intercept = hx;
			final = h_inter * cosf(no_fishy);
			current_texture = &game->textures.texture[N_N]; // Use north texture for horizontal walls
		}
		float wall_h = (64 / final) * (960 / pierce);
		draw_vertical_line(game, ray, wall_h, 1080, final, current_texture, intercept);
		ray++;
		ray_angle += offset;
		if (ray_angle < 0)
			ray_angle += (2 * PI);
		else if (ray_angle > (2 * PI))
			ray_angle -= (2 * PI);
	}
}
