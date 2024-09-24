/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/24 12:29:24 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 64)
	{
		j = x - 1;
		while (++j < x + 64)
			mlx_pixel_put(game->mlx, game->window, j, i, colour);
	}
}

void	rendermap(t_game *game)
{
	int i = -1;
	int j;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
			if (game->map.map[i][j] == WALL)
				draw_wall(game, j * 64, i * 64, 0xb8bfc2);
	}
}