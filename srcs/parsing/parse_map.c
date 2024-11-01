/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:53:35 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/01 22:24:49 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
// #include <math.h>

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

void	get_angle(t_game *game, char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				if (map[i][j] == 'N')
					game->map.angle = (3 * PI) / 2;
				else if (map[i][j] == 'E')
					game->map.angle = 0;
				else if (map[i][j] == 'W')
					game->map.angle = PI;
				else if (map[i][j] == 'S')
					game->map.angle = PI / 2;
			}
			j++;
		}
		i++;
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
	get_angle(game, map->map, map->height);
	map->map[i] = NULL;
}
