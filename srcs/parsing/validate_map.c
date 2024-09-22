/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:54:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 19:03:28 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_player(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (ft_strchr("NEWS", map->map[i][j]))
			{
				if (!map->player)
				{
					map->player_y = i;
					map->player_x = j;
					map->player = map->map[i][j];
				}
				else
					(printf("Broddie u can only have one\n"), exit(1));
					//FREEEEEE
			}
		}
	}
	//FREEEEEE
	if (!map->player)
		(printf("soo.... u dont wanna play?\n"), exit(1));
}

void	no_void(t_map *map)
{
	int		i;
	int		j;	
	char	invalid;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == ' ')
				invalid = '0';
			else if (map->map[i][j] == map->player)
				invalid = ' ';
			else if (map->map[i][j] == DOOR)
				invalid = ' ';
			else
				continue ;
			if (j > 0 && map->map[i][j - 1] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (j < map->width - 1 && map->map[i][j + 1] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (i > 0 && map->map[i - 1][j] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (i < map->height - 1 && map->map[i + 1][j] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			//FREEEEEEEEEEE
		}
	}
}

void	validate_map(t_map *map)
{
	check_player(map);
	no_void(map);
}