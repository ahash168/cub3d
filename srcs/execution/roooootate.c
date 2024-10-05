/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roooootate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:11 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/05 15:20:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rotate_player(t_game *game)
{
	if (game->keys.right)
		game->map.angle += 0.035;
	if (game->keys.left)
		game->map.angle += -0.035;
	if (game->map.angle < 0)
		game->map.angle += 2 * PI;
	if (game->map.angle >= (2 * PI))
		game->map.angle -= 2 * PI;
	return (0);
}
