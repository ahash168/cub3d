/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooooove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/01 10:45:52 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move(float new_x, float new_y, t_game *game)
{
	game->map.player_x = new_x;
	game->map.player_y = new_y;
	rendermap(game);
}

int	move_player(int keypress, t_game *game)
{
	if (keypress == W)
	{
		game->map.player_x += 0.12 * cos(game->map.angle);
		game->map.player_y += 0.12 * sin(game->map.angle);
	}
	if (keypress == A)
	{
		game->map.player_x += 0.12 * cos(game->map.angle - (PI / 2));
		game->map.player_y += 0.12 * sin(game->map.angle - (PI / 2));
	}
	if (keypress == S)
	{
		game->map.player_x += -0.12 * cos(game->map.angle);
		game->map.player_y += -0.12 * sin(game->map.angle);
	}
	if (keypress == D)
	{
		game->map.player_x += 0.12 * cos(game->map.angle + (PI / 2));
		game->map.player_y += 0.12 * sin(game->map.angle + (PI / 2));
	}
	move(game->map.player_x, game->map.player_y, game);
	return (0);
}
