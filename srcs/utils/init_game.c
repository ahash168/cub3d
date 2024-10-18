/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:36:50 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/17 12:38:32 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_file(t_file *file)
{
	file->file = NULL;
	file->fd = -1;
	file->file_size = 1;
}

void	init_textures(t_textures *textures)
{
	textures->pointers.north = NULL;
	textures->pointers.east = NULL;
	textures->pointers.west = NULL;
	textures->pointers.south = NULL;
	textures->pointers.ceiling = NULL;
	textures->pointers.floor = NULL;
	textures->strings.north = NULL;
	textures->strings.east = NULL;
	textures->strings.west = NULL;
	textures->strings.south = NULL;
	textures->strings.ceiling = NULL;
	textures->strings.floor = NULL;
	textures->floor = -1;
	textures->ceiling = -1;
	textures->s.glow = NULL;
	textures->s.stick[0] = NULL;
	textures->s.stick[1] = NULL;
	textures->s.stick[2] = NULL;
	textures->s.stick[3] = NULL;
	textures->s.stick[4] = NULL;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->angle = 0;
	map->player = 0;
}

void	init_counter(t_counter *counter)
{
	clock_gettime(CLOCK_MONOTONIC, &(counter->previous));
	clock_gettime(CLOCK_MONOTONIC, &(counter->now));
	counter->c = 0;
}

void	init_game(t_game *game)
{
	init_file(&game->file);
	init_textures(&game->textures);
	init_map(&game->map);
	init_counter(&game->counter);
	game->mlx = mlx_init();
	game->window = NULL;
}
