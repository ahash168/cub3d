/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:49:03 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 18:12:12 by tabadawi         ###   ########.fr       */
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
	// ERROR HANDLE -error message and exit and free file and textures
	if (!collected_textures(&game->textures))
		(printf("couldnt get them all\n"), exit(1));
	get_map(&file, &game->map, index);
	free_array(file.file);
	validate_map(&game->map);
	// VALIDATE_MAP
}
