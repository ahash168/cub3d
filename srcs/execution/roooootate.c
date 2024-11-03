/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:26:39 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define _C3D_ROT_SPEED	0.060f

int	rotate_player(t_game *game)
{
	if (game->keys.right)
		game->map.angle += _C3D_ROT_SPEED;
	if (game->keys.left)
		game->map.angle += -_C3D_ROT_SPEED;
	if (game->map.angle < 0)
		game->map.angle += 2.f * M_PI;
	if (game->map.angle >= 2.f * M_PI)
		game->map.angle -= 2.f * M_PI;
	return (0);
}
