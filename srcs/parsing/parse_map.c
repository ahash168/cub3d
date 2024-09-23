/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:53:35 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/23 19:47:13 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_line(char *str, int flag, t_game *game)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("10NEWSD ", str[i]))
		{
			if (flag)
				errorer(game, 3, BAD_LMNT);
			return (0);
		}
	}
	return (1);
}

void	check_len(int index, t_map *map, t_file *file, t_game *game)
{
	int	width;

	width = 0;
	map->width = ft_strlen(file->file[index]);
	while (file->file[index] && map_line(file->file[index], 1, game))
	{
		width = ft_strlen(file->file[index]);
		if (width > map->width)
			map->width = width;
		index++;
		map->height++;
	}
}

void	get_map(t_game *game, t_map *map, int index)
{
	int	i;

	init_map(map);
	check_len(index, map, &game->file, game);
	if (!map->height)
		errorer(game, 3, NO_MAP);
	if (map->height < 3)
		errorer(game, 3, SMOL_MAP);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		errorer(game, 3, MALLOC);
	i = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		ft_strlcpy(map->map[i], game->file.file[index], map->width + 1);
		while ((int)ft_strlen(map->map[i]) < map->width)
			ft_strlcat(map->map[i], " ", map->width + 1);
		i++;
		index++;
	}
	map->map[i] = NULL;
}
