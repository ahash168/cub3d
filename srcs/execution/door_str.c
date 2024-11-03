/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:05:53 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:26:57 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	door_checker(t_game *game, int x, int y, char c)
{
	if (((game->map.angle >= 45 * DR && game->map.angle < 135 * DR)
			&& game->map.map[y + 1][x] == c)
			|| ((game->map.angle >= 135 * DR && game->map.angle < 225 * DR)
			&& game->map.map[y][x - 1] == c)
			|| ((game->map.angle >= 225 * DR && game->map.angle < 315 * DR)
			&& game->map.map[y - 1][x] == c)
			|| (((game->map.angle >= 315 * DR && game->map.angle < 360 * DR)
			|| (game->map.angle >= 0 * DR && game->map.angle < 45 * DR))
			&& game->map.map[y][x + 1] == c))
		return (1);
	return (0);
}

void	door_str(t_game *game)
{
	int		x;
	int		y;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	if (door_checker(game, x, y, 'D'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, \
		"OPEN DOORRRR [E]");
	else if (door_checker(game, x, y, 'O'))
		mlx_string_put(game->mlx, game->window, 960, 540, 0xFFFFFF, \
		"CLOSE DOORRRR [E]");
}
