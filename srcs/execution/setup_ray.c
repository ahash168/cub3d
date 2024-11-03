/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:24:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:23:35 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	limit_angle(float *angle, float offset)
{
	(*angle) += offset;
	if ((*angle) < 0)
		(*angle) += (2 * M_PI);
	else if ((*angle) > (2 * M_PI))
		(*angle) -= (2 * M_PI);
}

t_data	*select_txtr(float angle, int door_flag, int is_vertical, t_game *game)
{
	if (door_flag)
		return (&game->textures.door);
	if (is_vertical)
	{
		if (angle > M_PI / 2 && angle <= 3 * M_PI / 2)
			return (&game->textures.texture[W_N]);
		else
			return (&game->textures.texture[E_N]);
	}
	else
	{
		if (angle > 0 && angle <= M_PI)
			return (&game->textures.texture[S_N]);
		else
			return (&game->textures.texture[N_N]);
	}
}

void	setup_ray(t_game *game, t_ray_data *ray, float angle)
{
	ray->fisheye = game->map.angle - angle;
	limit_angle(&ray->fisheye, 0);
	ray->v_inter = get_v_inter(game, angle, ray);
	ray->h_inter = get_h_inter(game, angle, ray);
	if (ray->v_inter < ray->h_inter)
	{
		ray->intercept = ray->vy;
		ray->distance = ray->v_inter * cosf(ray->fisheye);
		ray->current_texture = select_txtr(angle, ray->door_flag_v, 1, game);
	}
	else
	{
		ray->intercept = ray->hx;
		ray->distance = ray->h_inter * cosf(ray->fisheye);
		ray->current_texture = select_txtr(angle, ray->door_flag_h, 0, game);
	}
}

void	init_ray(t_ray_data *ray)
{
	ray->h_inter = 0;
	ray->v_inter = 0;
	ray->hx = 0;
	ray->hy = 0;
	ray->vx = 0;
	ray->vy = 0;
	ray->distance = 0;
	ray->fisheye = 0;
	ray->wall_h = 0;
	ray->door_flag_h = 0;
	ray->door_flag_v = 0;
	ray->intercept = 0;
	ray->current_texture = NULL;
}
