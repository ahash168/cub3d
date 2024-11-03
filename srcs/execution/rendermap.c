/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendermap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:08:17 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:28:43 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rendermap(t_game *game)
{
	game->counter = (game->counter + 1) % (4 * 10);
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, \
	&game->img.line_length, &game->img.endian);
	rays(game, game->rays);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->img.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, \
	game->textures.s.stick[game->counter / 10], 1100, 790);
	door_str(game);
	mlx_destroy_image(game->mlx, game->img.img);
}
