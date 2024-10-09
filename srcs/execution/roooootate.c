/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/08 20:35:41 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rotate_player(t_game *game)
{
	if (game->keys.right)
		game->map.angle += 0.005;
	if (game->keys.left)
		game->map.angle += -0.005;
	if (game->map.angle < 0)
		game->map.angle += 2 * PI;
	if (game->map.angle >= (2 * PI))
		game->map.angle -= 2 * PI;
	return (0);
}
