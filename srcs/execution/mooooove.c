/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooooove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:10:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/24 20:39:29 by tabadawi         ###   ########.fr       */
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
	if (keypress == ESC)
		close_game(game, 0);
	if (keypress == UP || keypress == W)
		move(game->map.player_x, game->map.player_y - 0.1, game);
	if (keypress == DOWN || keypress == S)
		move(game->map.player_x, game->map.player_y + 0.1, game);
	if (keypress == LEFT || keypress == A)
		move(game->map.player_x - 0.1, game->map.player_y, game);
	if (keypress == RIGHT || keypress == D)
		move(game->map.player_x + 0.1, game->map.player_y, game);
	return (0);
}
