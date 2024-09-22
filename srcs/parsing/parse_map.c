/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:53:35 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 18:41:40 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_line(char *str, int flag)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr("10NEWSD ", str[i]))
		{
			if (flag)
				(printf("BAD ELEMENT\n"), exit(1));
			return (0);
		}
	return (1);
}

void	check_len(int index, t_map *map, t_file *file)
{
	int	width;

	width = 0;
	map->width = ft_strlen(file->file[index]);
	while (file->file[index] && map_line(file->file[index], 1))
	{
		width = ft_strlen(file->file[index]);
		if (width > map->width)
			map->width = width;
		index++;
		map->height++;
	}
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player = 0;
}

void	get_map(t_file *file, t_map *map, int index)
{
	int	i;
	int	t;

	init_map(map);
	check_len(index, map, file);
	// FREEEEEE
	if (map->height < 3)
		(printf("womp womp map problem\n"), exit(1));
	map->map = malloc(sizeof(char *) * (map->height + 1));
	// FREEEEEE
	if (!map->map)
		exit(1);
	i = 0;
	printf("map height: %d\n", map->height);
	printf("map width: %d\n", map->width);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		ft_strlcpy(map->map[i], file->file[index], map->width + 1);
		while ((int)ft_strlen(map->map[i]) < map->width)
			ft_strlcat(map->map[i], " ", map->width + 1);
		i++;
		index++;
	}
	map->map[i] = NULL;
	t = 0;
	while (map->map[t])
	{
		printf("<<%s>>\n", map->map[t]);
		t++;
	}
}
