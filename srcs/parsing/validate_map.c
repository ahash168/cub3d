/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:54:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/30 16:25:45 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_player(t_map *map, t_game *game)
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
					map->player_y = i + 0.5;
					map->player_x = j + 0.5;
					map->player = map->map[i][j];
					map->map[i][j] = '0';
				}
				else
					errorer(game, 3, XTRA_PLYR);
			}
		}
	}
	if (!map->player)
		errorer(game, 3, NO_PLYR);
}

void	check_voidy(int i, int j, t_game *game, int invalid)
{
	if (j > 0 && game->map.map[i][j - 1] == invalid)
		errorer(game, 3, VOID);
	if (j < game->map.width - 1 && game->map.map[i][j + 1] == invalid)
		errorer(game, 3, VOID);
	if (i > 0 && game->map.map[i - 1][j] == invalid)
		errorer(game, 3, VOID);
	if (i < game->map.height - 1 && game->map.map[i + 1][j] == invalid)
		errorer(game, 3, VOID);
}

void	no_void(t_map *map, t_game *game)
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
			check_voidy(i, j, game, invalid);
		}
	}
}

void	parse_doors(t_map *map, t_game *game)
{
	int	i;
	int	j;
	int	valid;

	i = -1;
	valid = 1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == DOOR)
			{
				if (map->map[i - 1][j] == WALL)
				{
					if (map->map[i + 1][j] == WALL)
						if (map->map[i][j - 1] == FLOOR)
							if (map->map[i][j + 1] == FLOOR)
								valid = 0;
				}
				else if (map->map[i][j - 1] == WALL)
				{
					if (map->map[i][j + 1] == WALL)
						if (map->map[i - 1][j] == FLOOR)
							if (map->map[i + 1][j] == FLOOR)
								valid = 0;
				}
				else 
					errorer(game, 3, DOOR_ERR);
			}
		}
	}
}

void	validate_map(t_map *map, t_game *game)
{
	check_player(map, game);
	no_void(map, game);
	parse_doors(map, game);
}
