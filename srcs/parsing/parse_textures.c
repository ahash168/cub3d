/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:51:09 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 17:53:14 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_textures(t_textures *textures)
{
	textures->pointers.east = NULL;
	textures->pointers.north = NULL;
	textures->pointers.south = NULL;
	textures->pointers.west = NULL;
	textures->pointers.ceiling = NULL;
	textures->pointers.floor = NULL;
	textures->strings.north = NULL;
	textures->strings.east = NULL;
	textures->strings.west = NULL;
	textures->strings.south = NULL;
	textures->strings.ceiling = NULL;
	textures->strings.floor = NULL;
	textures->ceiling = -1;
	textures->floor = -1;
}

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
				//need to free file.file before exiting
				if (map_line(file->file[i], 0))
					(printf("couldnt get all textures\n"), exit (1));
				else
					(printf("%s: not a texture\n", file->file[i]), exit (1));
			}
		}
	}
	while (file->file[i] && empty_line(file->file[i]))
		i++;
	printf("ceiling: %x\n", textures->ceiling);
	printf("floor: %x\n", textures->floor);
	return (i);
}
