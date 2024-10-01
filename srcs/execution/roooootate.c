/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/30 21:06:01 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(float angle, t_game *game)
{
    draw_direction_vector(game, game->mlx, game->window, game->map.player_x + 50, game->map.player_y + 50, game->map.angle + angle, 0xFF0000);  // Red vector
	game->map.angle += angle;
	// rendermap(game);
}

int	rotate_player(int keypress, t_game *game)
{
	if (keypress == RIGHT)
		rotate(0.0174533, game);
	if (keypress == LEFT)
		rotate(-0.0174533, game);
	return (0);
}
