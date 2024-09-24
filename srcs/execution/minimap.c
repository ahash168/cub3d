/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:24:35 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/24 20:37:52 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_player(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 63)
	{
		j = x - 1;
		while (++j < x + 63)
			pixel_put(&game->img, j, i, colour);
	}
}

void	draw_wall(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 63)
	{
		j = x - 1;
		while (++j < x + 63)
			pixel_put(&game->img, j, i, colour);
	}
}

void	draw_floor(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 63)
	{
		j = x - 1;
		if (i == y || i == y + 63)
		{
			while (++j < x + 63)
			{
				pixel_put(&game->img, j, i, colour);
				pixel_put(&game->img, j, i + (i == y), colour);
				pixel_put(&game->img, j, i - (i == y + 63), colour);
			}
		}
		else
		{
			pixel_put(&game->img, j + 1, i, colour);
			pixel_put(&game->img, j + 2, i, colour);
			pixel_put(&game->img, j + 62, i, colour);
			pixel_put(&game->img, j + 63, i, colour);
		}
	}
}

void	draw_map(t_game *game)
{
	int i = -1;
	int j;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == '1')
				draw_wall(game, j * 64, i * 64, 0xb8bfc2);
			else if (game->map.map[i][j] == ' ')
				draw_wall(game, j * 64, i * 64, 0x242424);
			else
				draw_floor(game, j * 64, i * 64, 0xf7adbc);
		}
	}	
}

void	rendermap(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->map.width * 64, game->map.height *64);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_length, &game->img.endian);
	draw_map(game);
	draw_player(game, game->map.player_x * 64, game->map.player_y * 64, 0x2a9df5);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	mlx_destroy_image(game->mlx, game->img.img);
}