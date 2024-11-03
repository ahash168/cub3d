/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:36:50 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 11:29:18 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_textures(t_textures *textures)
{
	textures->texture[N_N].img = NULL;
	textures->texture[E_N].img = NULL;
	textures->texture[W_N].img = NULL;
	textures->texture[S_N].img = NULL;
	textures->texture[C_N].img = NULL;
	textures->texture[F_N].img = NULL;
	textures->door.img = NULL;
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

void	init_file(t_file *file)
{
	file->file = NULL;
	file->fd = -1;
	file->file_size = 1;
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

void	init_game(t_game *game)
{
	init_file(&game->file);
	init_textures(&game->textures);
	init_map(&game->map);
	game->counter = 0;
	game->mlx = mlx_init();
	game->window = NULL;
	game->fov_rd = 60.f * DR;
	game->wall_factor = 960.f / tanf(game->fov_rd / 2.f);
	game->offset = game->fov_rd / WINDOW_W;
}
