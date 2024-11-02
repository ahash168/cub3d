/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/02 21:57:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533f
#define P2	PI/2.f
#define P3	3.f * PI/2
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
	int		final;
	float	dist_max_min_avg = 1.f - ((distance - MINIMUM) / (MAXIMUM - MINIMUM));

	tex_x = (int)(huh * (texture->width / 64));
	if (tex_x >= texture->width)
		tex_x = tex_x - (tex_x / texture->width) * texture->width;
	if (h < window_height)
	{
		float	half_height = (window_height - h) / 2.f;
		float	factor2 = texture->height/ h;
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
		(void) final;
		while (y < window_height)
		{
			int clr = shade_floor(game->textures.floor, y, window_height);
			pixel_put(&game->img, x, y, clr);
			y++;
		}
	}
	else if (h > window_height)
	{
		float factor = texture->height/ h;
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

int	find_wall(float x, float y, t_game *game, int *door_flag)
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
	{
		if (game->map.map[map_y][map_x] == '1')
			return (0);
		else if (game->map.map[map_y][map_x] == 'D')
		{
			*door_flag = 1;
			return (0);
		}
	}
	return (1);
}

int	get_h_inter(t_game *game, float ray_angle, t_ray_data *ray)
{
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = 64;
	x_step = 64 / tan(ray_angle);
	ray->hy = floor((game->map.player_y * 64) / 64) * 64;
	pixel = inter_check(ray_angle, &ray->hy, &y_step, 1);
	ray->hx = ((game->map.player_x * 64)) + (ray->hy - ((game->map.player_y * 64))) / tan(ray_angle);
	if ((unit_circle(ray_angle, 'y') && x_step > 0) || (!unit_circle(ray_angle, 'y') && x_step < 0))
		x_step *= -1;
	while (find_wall(ray->hx, ray->hy - pixel, game, &ray->door_flag_h))
	{
		ray->hx += x_step;
		ray->hy += y_step;
	}
	return (sqrt(pow(ray->hx - ((game->map.player_x * 64)), 2) + pow(ray->hy - ((game->map.player_y * 64)), 2)));
}

int	get_v_inter(t_game *game, float ray_angle, t_ray_data *ray)
{
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = 64;
	y_step = 64 * tan(ray_angle);
	ray->vx = floor((game->map.player_x * 64) / 64) * 64;
	pixel = inter_check(ray_angle, &ray->vx, &x_step, 0);
	ray->vy = (game->map.player_y * 64) + (ray->vx - (game->map.player_x * 64)) * tan(ray_angle);
	if ((unit_circle(ray_angle, 'x') && y_step < 0) || (!unit_circle(ray_angle, 'x') && y_step > 0))
		y_step *= -1;
	while (find_wall(ray->vx - pixel, ray->vy, game, &ray->door_flag_v))
	{
		ray->vx += x_step;
		ray->vy += y_step;
	}
	return (sqrt(pow(ray->vx - (game->map.player_x * 64), 2) + pow(ray->vy - (game->map.player_y * 64), 2)));
}

void	limit_angle(float *angle, float offset)
{
	(*angle) += offset;
	if ((*angle) < 0)
		(*angle) += (2 * M_PI);
	else if ((*angle) > (2 * M_PI))
		(*angle) -= (2 * M_PI);
}

void	init_ray(t_game *game, t_ray_data *ray, float angle)
{
	//its so funny, smth is wrong w this flag, and ik what it is
	ray->door_flag_h = 0;
	ray->door_flag_v = 0;
	ray->fisheye = game->map.angle - angle;
	limit_angle(&ray->fisheye, 0);
	ray->v_inter = get_v_inter(game, angle, ray);
	ray->h_inter = get_h_inter(game, angle, ray);
	if (ray->v_inter < ray->h_inter)
	{
		ray->intercept = ray->vy;
		ray->distance = ray->v_inter * cosf(ray->fisheye);
		if (!ray->door_flag_v)
		{
			if (angle > PI / 2 && angle <= 3 * PI / 2)
				ray->current_texture = &game->textures.texture[W_N];
			else
				ray->current_texture = &game->textures.texture[E_N];
		}
		else
			ray->current_texture = &game->textures.door;

	}
	else
	{
		ray->intercept = ray->hx;
		ray->distance = ray->h_inter * cosf(ray->fisheye);
		if (!ray->door_flag_h)
		{
			if (angle > 0 && angle <= PI)
				ray->current_texture = &game->textures.texture[S_N];
			else
				ray->current_texture = &game->textures.texture[N_N];
		}
		else
			ray->current_texture = &game->textures.door;
	}
	// if (ray->door_flag)
	// 	ray->current_texture = &game->textures.door;
}

void	rays(t_game *game, t_ray_data *ray_arr)
{
	int		r;
	// t_data	*current_texture;
	float	ray_angle;

	r = 0;
	ray_angle = game->map.angle - (game->fov_rd / 2.f);
	limit_angle(&ray_angle, 0);
	while (r < WINDOW_W)
	{
		init_ray(game, &ray_arr[r], ray_angle);
		ray_arr[r].wall_h = (64 / ray_arr[r].distance) * game->wall_factor;
		draw_vertical_line(game, r, ray_arr[r].wall_h, WINDOW_H, \
		ray_arr[r].distance, ray_arr[r].current_texture, ray_arr[r].intercept);
		//this function (d_v_l) will change A LOT once you are done w ur part
		r++;
		limit_angle(&ray_angle, game->offset);
	}
}

// i think u can also add a flag to the struct to determine if we landed on a wall or not
// so instead of worrying ab picking the side of the wall u js render the door immediately
// so itll be oh if this flag, assign the texture to door, else, check wall sides