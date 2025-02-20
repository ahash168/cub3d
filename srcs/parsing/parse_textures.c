/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:51:09 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/23 19:52:36 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	collected_textures(t_textures *textures)
{
	if (textures->strings.east
		&& textures->strings.west
		&& textures->strings.south
		&& textures->strings.north
		&& textures->floor != -1
		&& textures->ceiling != -1)
		return (1);
	return (0);
}

int	check_texture(char *str, t_textures *textures, t_game *game)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, (char **)&textures->strings.north, game, 1);
	else if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, (char **)&textures->strings.south, game, 1);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		assign_texture(str, (char **)&textures->strings.west, game, 1);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		assign_texture(str, (char **)&textures->strings.east, game, 1);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		assign_colour(str, &textures->ceiling, textures->c_arr, game);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		assign_colour(str, &textures->floor, textures->f_arr, game);
	else
		return (0);
	return (1);
}

int	get_textures(t_file *file, t_textures *textures, t_game *game)
{
	int	i;

	i = -1;
	init_textures(textures);
	while (file->file[++i])
	{
		if (collected_textures(textures))
			break ;
		if (!empty_line(file->file[i]))
		{
			if (!check_texture(file->file[i], textures, game))
			{
				if (map_line(file->file[i], 0, game))
					errorer(game, 3, CANT_TXTR);
				else
					errorer(game, 3, NOT_TXTR);
			}
		}
	}
	while (file->file[i] && empty_line(file->file[i]))
		i++;
	return (i);
}
