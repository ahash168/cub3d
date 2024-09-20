/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:49:03 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/20 21:01:47 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parsing(char *path, t_game *game)
{
	int			index;
	t_file		file;

	index = 0;
	validate_file(path, &file);
	get_file(path, &file);
	index += get_textures(&file, &game->textures, game);
	// ERROR HANDLE -error message and exit
	if (!collected_textures(&game->textures))
		(printf("couldnt get them all\n"), exit(1));
	get_map(&file, &game->map, index);
	free_array(file.file);
	check_closed(&game->map);
	check_player(&game->map);
	no_void(&game->map);
	// VALIDATE_MAP
}
