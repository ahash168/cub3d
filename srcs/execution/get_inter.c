/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:28:13 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:28:24 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > M_PI_2 && angle < 3 * M_PI_2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
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
		if (!(angle > M_PI_2 && angle < 3 * M_PI_2))
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
	int	map_x;
	int	map_y;

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
	ray->hx = ((game->map.player_x * 64)) + \
		(ray->hy - ((game->map.player_y * 64))) / tan(ray_angle);
	if ((unit_circle(ray_angle, 'y') && x_step > 0) \
		|| (!unit_circle(ray_angle, 'y') && x_step < 0))
		x_step *= -1;
	while (find_wall(ray->hx, ray->hy - pixel, game, &ray->door_flag_h))
	{
		ray->hx += x_step;
		ray->hy += y_step;
	}
	return (sqrt(pow(ray->hx - ((game->map.player_x * 64)), 2) + \
		pow(ray->hy - ((game->map.player_y * 64)), 2)));
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
	ray->vy = (game->map.player_y * 64) + \
		(ray->vx - (game->map.player_x * 64)) * tan(ray_angle);
	if ((unit_circle(ray_angle, 'x') && y_step < 0) \
		|| (!unit_circle(ray_angle, 'x') && y_step > 0))
		y_step *= -1;
	while (find_wall(ray->vx - pixel, ray->vy, game, &ray->door_flag_v))
	{
		ray->vx += x_step;
		ray->vy += y_step;
	}
	return (sqrt(pow(ray->vx - (game->map.player_x * 64), 2) + \
		pow(ray->vy - (game->map.player_y * 64), 2)));
}
