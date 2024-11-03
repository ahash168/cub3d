/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:27:38 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:27:26 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_door(t_game *game, float a, int open, int which)
{
	int		x;
	int		y;
	float	angle;
	char	c;
	int		inc;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	if (which == 1)
		y += 1;
	else if (which == 2)
		x -= 1;
	else if (which == 3)
		y -= 1;
	else if (which == 4)
		x += 1;
	angle = game->map.angle;
	limit_angle(&angle, 0);
	inc = 1 + ((a == 315 * DR) || (a == 0));
	c = 'D';
	if (open == 1)
		c += 11;
	if ((angle >= a && angle < a + M_PI / inc) && game->map.map[y][x] == c)
		return (1);
	return (0);
}

void	doors(t_game *game)
{
	int		x;
	int		y;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	if (check_door(game, 45 * DR, 0, 1))
		game->map.map[y + 1][x] = 'O';
	else if (check_door(game, 135 * DR, 0, 2))
		game->map.map[y][x - 1] = 'O';
	else if (check_door(game, 255 * DR, 0, 3))
		game->map.map[y - 1][x] = 'O';
	else if (check_door(game, 315 * DR, 0, 4) || check_door(game, 0, 0, 4))
		game->map.map[y][x + 1] = 'O';
	else if (check_door(game, 45 * DR, 1, 1))
		game->map.map[y + 1][x] = 'D';
	else if (check_door(game, 135 * DR, 1, 2))
		game->map.map[y][x - 1] = 'D';
	else if (check_door(game, 255 * DR, 1, 3))
		game->map.map[y - 1][x] = 'D';
	else if (check_door(game, 315 * DR, 1, 4) || check_door(game, 0, 1, 4))
		game->map.map[y][x + 1] = 'D';
}
