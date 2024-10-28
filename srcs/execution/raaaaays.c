/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/28 13:08:56 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533f
#define P2	PI/2.f
#define P3	3.f * PI/2
#define WINDOW_W 1920
#define WINDOW_H 1080
#define MINIMUM 50.f
#define MAXIMUM 350.f
#define MINIMUMF 50.f
#define MAXIMUMF 350.f

typedef struct s_trgb
{
	unsigned int	trgb;
	unsigned int	shaded;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_trgb;

int	change_shade(int colour, float dist, float avg)
{
	float			shade_factor;
	t_trgb			new;

	shade_factor = (dist <= MINIMUM) * 1.f + (dist >= MAXIMUM) * 0.f;
	if (dist > MINIMUM && dist < MAXIMUM)
	{
		shade_factor = avg;
		if (shade_factor < 0.0f)
			shade_factor = 0.0f;
		if (shade_factor > 1.0f)
			shade_factor = 1.0f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	shade_floor(int colour, int y, int window_height)
{
	float	shade_factor;
	t_trgb	new;
	int		check;

	check = window_height - y;
	if (check <= MINIMUMF)
		shade_factor = 1.f;
	else if (check >= MAXIMUMF)
		shade_factor = 0.f;
	else
	{
		shade_factor = 1.f - (((check) - MINIMUMF) / (MAXIMUMF - MINIMUMF));
		if (shade_factor < 0.f)
			shade_factor = 0.f;
		if (shade_factor > 1.f)
			shade_factor = 1.f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	get_pixel_color_from_texture(t_data *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_vertical_line(t_game *game, int x, float h, int window_height, float distance, t_data *texture, float huh)
{
	int		y = 0;
	int		i = 0;
	int		tex_x, tex_y;
	int		tex_height = 256;
	int		tex_width = 256;
	int		final;
	float	dist_max_min_avg = 1.f - ((distance - MINIMUM) / (MAXIMUM - MINIMUM));

	tex_x = (int)(huh * (tex_width / 64));
	if (tex_x >= tex_width)
		tex_x = tex_x - (tex_x / tex_width) * tex_width;
	if (h < window_height)
	{
		float	half_height = (window_height - h) / 2.f;
		float	factor2 = tex_height / h;
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
			color = change_shade(color, distance, dist_max_min_avg);
			pixel_put(&game->img, x, y, color);
			y++;
		}
		final = y;
		while (y < window_height)
		{
			int clr = shade_floor(game->textures.floor, y, window_height);
			pixel_put(&game->img, x, y, clr);
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
			color = change_shade(color, distance, dist_max_min_avg);
			pixel_put(&game->img, x, y, color);
			start++;
			y++;
		}
	}
}

int unit_circle(float angle, char c)
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

int inter_check(float angle, float *inter, float *step, int is_horizon)
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

int	find_wall(float x, float y, t_game *game)
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
		if (game->map.map[map_y][map_x] == '1' || game->map.map[map_y][map_x] == 'D')
			return (0);
	return (1);
}

int	get_h_inter(t_game *game, float ray_angle, float *hx, float *hy)
{
	float	x_step;
	float	y_step;
	int		pixel;

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
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = 64;
	y_step = 64 * tan(ray_angle);
	*vx = floor((game->map.player_x * 64) / 64) * 64;
	pixel = inter_check(ray_angle, vx, &x_step, 0);
	*vy = (game->map.player_y * 64) + (*vx - (game->map.player_x * 64)) * tan(ray_angle);
	if ((unit_circle(ray_angle, 'x') && y_step < 0) || (!unit_circle(ray_angle, 'x') && y_step > 0))
		y_step *= -1;
	while (find_wall(*vx - pixel, *vy, game))
	{
		*vx += x_step;
		*vy += y_step;
	}
	return (sqrt(pow(*vx - (game->map.player_x * 64), 2) + pow(*vy - (game->map.player_y * 64), 2)));
}

void	raaaaays(t_game *game)
{
	float	fov_rd;
	float	h_inter;
	float	v_inter;
	float	ray;
	float	ray_angle;
	float	offset;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	final;
	float	no_fishy;
	fov_rd = 60.0f * DR;
	float	pierce = tanf(fov_rd / 2.f);
	t_data	*current_texture;

	h_inter = 0.0f;
	v_inter = 0.0f;
	ray = 0;
	ray_angle = game->map.angle - (fov_rd / 2.f);
	if (ray_angle < 0)
		ray_angle += (2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (2 * PI);
	offset = fov_rd / WINDOW_W;
	while (ray < WINDOW_W)
	{
		no_fishy = game->map.angle - ray_angle;
		if (no_fishy < 0)
			no_fishy += (2 * PI);
		else if (no_fishy > (2 * PI))
			no_fishy -= (2 * PI);
		h_inter = get_h_inter(game, ray_angle, &hx, &hy);
		v_inter = get_v_inter(game, ray_angle, &vx, &vy);
		float	intercept = 0;
		if (v_inter < h_inter)
		{
			intercept = vy;
			final = v_inter * cosf(no_fishy);
			current_texture = &game->textures.texture[W_N];
		}
		else
		{
			intercept = hx;
			final = h_inter * cosf(no_fishy);
			current_texture = &game->textures.texture[N_N];
		}
		float	wall_h = (64 / final) * (960 / pierce);
		draw_vertical_line(game, ray, wall_h, 1080, final, current_texture, intercept);
		ray++;
		ray_angle += offset;
		if (ray_angle < 0)
			ray_angle += (2 * PI);
		else if (ray_angle > (2 * PI))
			ray_angle -= (2 * PI);
	}
}
