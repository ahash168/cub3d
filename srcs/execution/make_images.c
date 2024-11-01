/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:16:39 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/01 22:47:48 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_images(t_game *game)
{
	if (game->textures.s.stick[0])
		mlx_destroy_image(game->mlx, game->textures.s.stick[0]);
	if (game->textures.s.stick[1])
		mlx_destroy_image(game->mlx, game->textures.s.stick[1]);
	if (game->textures.s.stick[2])
		mlx_destroy_image(game->mlx, game->textures.s.stick[2]);
	if (game->textures.s.stick[3])
		mlx_destroy_image(game->mlx, game->textures.s.stick[3]);
	if (game->textures.s.stick[4])
		mlx_destroy_image(game->mlx, game->textures.s.stick[4]);
}

void	check_images(t_game *game)
{
	if (!game->textures.s.stick[0]
		|| !game->textures.s.stick[1] || !game->textures.s.stick[2]
		|| !game->textures.s.stick[3] || !game->textures.s.stick[4])
	{
		destroy_images(game);
		errorer(NULL, 3, IMG);
	}
}

// ok side note, our texture could vary and with that they could have different sizes
// what i want you to do is go to the t_data struct and add 2 vars, int height and width
// and then you can pass the address of them instead fo tile, for each texture and we will
// automatically have their sizes, so that later in drawing we can be more flexible rather
// than relying strictly on 256

void	make_images(t_game *game)
{
	int	tile;

	tile = 64;
	game->textures.s.stick[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/xpm/green.xpm", &tile, &tile);
	game->textures.s.stick[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/xpm/pink.xpm", &tile, &tile);
	game->textures.s.stick[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/xpm/blue.xpm", &tile, &tile);
	game->textures.s.stick[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/xpm/yellow.xpm", &tile, &tile);
	game->textures.s.stick[4] = mlx_xpm_file_to_image(game->mlx,
			"textures/xpm/yellow.xpm", &tile, &tile);
	game->textures.s.glow = game->textures.s.stick[0];
	check_images(game);
}
