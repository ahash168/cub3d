/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/01 10:48:49 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(float angle, t_game *game)
{
	game->map.angle += angle;
	rendermap(game);
}

int	rotate_player(int keypress, t_game *game)
{
	if (keypress == RIGHT)
		rotate(0.174533, game);
	if (keypress == LEFT)
		rotate(-0.174533, game);
	return (0);
}
