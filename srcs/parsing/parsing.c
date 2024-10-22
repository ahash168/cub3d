/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:49:03 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/24 11:53:24 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	xpm_image(t_game *game, char *file, void **texture)
{
	int	height;
	int	width;

	(*texture) = mlx_xpm_file_to_image(game->mlx, file, &width, &height);
	if (!(*texture))
		errorer(game, 3, XPM);
}

void	create_textures(t_game *game, t_textures *textures)
{
	xpm_image(game, (char *)textures->strings.north, &textures->pointers.north);
	xpm_image(game, (char *)textures->strings.east, &textures->pointers.east);
	xpm_image(game, (char *)textures->strings.west, &textures->pointers.west);
	xpm_image(game, (char *)textures->strings.south, &textures->pointers.south);
	if (textures->strings.ceiling)
		xpm_image(game, (char *)textures->strings.ceiling, &textures->pointers.ceiling);
	if (textures->strings.floor)
		xpm_image(game, (char *)textures->strings.floor, &textures->pointers.floor);
}

void	parsing(char *path, t_game *game)
{
	int			index;

	init_game(game);
	validate_file(path, &game->file);
	get_file(path, &game->file);
	index = get_textures(&game->file, &game->textures, game);
	if (!collected_textures(&game->textures))
		errorer(game, 3, CANT_TXTR);
	get_map(game, &game->map, index);
	validate_map(&game->map, game);
	create_textures(game, &game->textures);
}
