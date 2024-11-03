/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raaaaays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:43:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:49:48 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rays(t_game *game, t_ray_data *ray_arr)
{
	int		r;
	float	ray_angle;

	r = 0;
	ray_angle = game->map.angle - (game->fov_rd / 2.f);
	limit_angle(&ray_angle, 0);
	while (r < WINDOW_W)
	{
		init_ray(&ray_arr[r]);
		setup_ray(game, &ray_arr[r], ray_angle);
		ray_arr[r].wall_h = (64 / ray_arr[r].distance) * game->wall_factor;
		draw_vertical_line(game, r, &ray_arr[r]);
		r++;
		limit_angle(&ray_angle, game->offset);
	}
}
