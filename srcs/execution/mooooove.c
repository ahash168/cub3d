/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooooove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/23 17:47:29 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	move_player(t_game *game)
{
	float	x;
	float	y;
	
	x = game->map.player_x;
	y = game->map.player_y;
	if (game->keys.w)
	{
		x += 0.03 * cos(game->map.angle);
		y += 0.03 * sin(game->map.angle);
	}
	if (game->keys.a)
	{
		x += 0.03 * cos(game->map.angle - (PI / 2));
		y += 0.03 * sin(game->map.angle - (PI / 2));
	}
	if (game->keys.s)
	{
		x += -0.03 * cos(game->map.angle);
		y += -0.03 * sin(game->map.angle);
	}
	if (game->keys.d)
	{
		x += 0.03 * cos(game->map.angle + (PI / 2));
		y += 0.03 * sin(game->map.angle + (PI / 2));
	}
	if (game->map.map[(int) game->map.player_y][(int) x] == '0')
		game->map.player_x = x;
	if (game->map.map[(int) y][(int) game->map.player_x] == '0')
		game->map.player_y = y;
	return (0);
}
