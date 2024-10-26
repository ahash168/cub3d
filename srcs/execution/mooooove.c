/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooooove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/26 22:08:13 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define _C3D_SPEED 0.07f

void	new_pos(t_game *game, float x, float y)
{
	if (game->map.map[(int) game->map.player_y][(int) x] == '0'
		|| game->map.map[(int) game->map.player_y][(int) x] == 'O')
		game->map.player_x = x;
	if (game->map.map[(int) y][(int) game->map.player_x] == '0'
		|| game->map.map[(int) y][(int) game->map.player_x] == 'O')
		game->map.player_y = y;
}

void	update_values(t_game *game, float *x, float *y, float angle)
{
	float	speed;

	speed = _C3D_SPEED;
	if (game->keys.s)
		speed *= -1.f;
	(*x) += speed * cosf(game->map.angle + angle);
	(*y) += speed * sinf(game->map.angle + angle);
}

int	move_player(t_game *game)
{
	float	x;
	float	y;

	x = game->map.player_x;
	y = game->map.player_y;
	if (game->keys.w)
		update_values(game, &x, &y, 0.f);
	if (game->keys.a)
		update_values(game, &x, &y, -1.f * M_PI_2);
	if (game->keys.s)
		update_values(game, &x, &y, 0.f);
	if (game->keys.d)
		update_values(game, &x, &y, M_PI_2);
	new_pos(game, x, y);
	return (0);
}
