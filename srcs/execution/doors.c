/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:27:38 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/01 14:43:21 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533

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
	inc = 1 + ((a == 315) || (a == 0));
	if (open == 1)
		c = 'O';
	else
		c = 'D';
	if ((angle <= (a + PI / inc) && angle > a) && game->map.map[y][x] == c)
		return (1);
	return (0);
}

// idk if its here but the angle and door message dont always work on some
// angles so could you please check? use the "limit_angle" function with 0 as the offset
// u can pass the function as the param to check_door function, p sure thatll fix it

void	doors(t_game *game)
{
	int		x;
	int		y;
	float	angle;

	x = (int)game->map.player_x;
	y = (int)game->map.player_y;
	angle = game->map.angle;
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
