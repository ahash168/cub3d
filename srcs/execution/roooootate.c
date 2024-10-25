/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/24 20:24:19 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define _C3D_ROT_SPEED 0.060f
#define _C3D_2_PI 2.f*PI
int	rotate_player(t_game *game)
{
	if (game->keys.right)
		game->map.angle += _C3D_ROT_SPEED;
	if (game->keys.left)
		game->map.angle += -_C3D_ROT_SPEED;
	if (game->map.angle < 0)
		game->map.angle += _C3D_2_PI;
	if (game->map.angle >= _C3D_2_PI)
		game->map.angle -= _C3D_2_PI;
	return (0);
}
