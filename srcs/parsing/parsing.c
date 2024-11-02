/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:49:03 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/01 22:53:09 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parsing(char *path, t_game *game)
{
	int	index;

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
