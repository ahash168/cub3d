/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooooove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/24 20:24:30 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define _C3D_SPEED 0.07f
int	move_player(t_game *game)
{
	float	x;
	float	y;
	// const float cached_cos = cosf(game->map.angle - M_PI_2/*(PI / 2)*/);

	x = game->map.player_x;
	y = game->map.player_y;
	if (game->keys.w)
	{
		x += _C3D_SPEED * cosf(game->map.angle);
		y += _C3D_SPEED * sinf(game->map.angle);
	}
	if (game->keys.a)
	{
		x += _C3D_SPEED * cosf(game->map.angle - M_PI_2/*(PI / 2)*/);
		y += _C3D_SPEED * sinf(game->map.angle - M_PI_2/*(PI / 2)*/);
	}
	if (game->keys.s)
	{
		x += -_C3D_SPEED * cosf(game->map.angle);
		y += -_C3D_SPEED * sinf(game->map.angle);
	}
	if (game->keys.d)
	{
		x += _C3D_SPEED * cosf(game->map.angle + M_PI_2/*(PI / 2)*/);
		y += _C3D_SPEED * sinf(game->map.angle + M_PI_2/*(PI / 2)*/);
	}
	if (game->map.map[(int) game->map.player_y][(int) x] == '0')
		game->map.player_x = x;
	if (game->map.map[(int) y][(int) game->map.player_x] == '0')
		game->map.player_y = y;
	return (0);
}
