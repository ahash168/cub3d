/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:49:03 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/19 14:31:25 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	xpm_image(t_game *game, char *file, void **texture)
{
	int	height;
	int	width;

	(*texture) = mlx_xpm_file_to_image(game->mlx, file, &width, &height);
	if (!(*texture))
		errorer(game, 3, XPM);
}

void	create_textures(t_game *game, t_textures *textures)
{
	xpm_image(game, (char *)textures->strings.north, &textures->pointers.north);
	xpm_image(game, (char *)textures->strings.east, &textures->pointers.east);
	xpm_image(game, (char *)textures->strings.west, &textures->pointers.west);
	xpm_image(game, (char *)textures->strings.south, &textures->pointers.south);
	if (textures->strings.ceiling)
		xpm_image(game, (char *)textures->strings.ceiling, &textures->pointers.ceiling);
	if (textures->strings.floor)
		xpm_image(game, (char *)textures->strings.floor, &textures->pointers.floor);

	xpm_image(game, (char *)textures->strings.north, &textures->texture[N_N].img);
	textures->texture[N_N].addr = mlx_get_data_addr(textures->texture[N_N].img, &textures->texture[N_N].bpp, &textures->texture[N_N].line_length, &textures->texture[N_N].endian);
	xpm_image(game, (char *)textures->strings.east, &textures->texture[E_N].img);
	textures->texture[E_N].addr = mlx_get_data_addr(textures->texture[E_N].img, &textures->texture[E_N].bpp, &textures->texture[E_N].line_length, &textures->texture[E_N].endian);
	xpm_image(game, (char *)textures->strings.west, &textures->texture[W_N].img);
	textures->texture[W_N].addr = mlx_get_data_addr(textures->texture[W_N].img, &textures->texture[W_N].bpp, &textures->texture[W_N].line_length, &textures->texture[W_N].endian);
	xpm_image(game, (char *)textures->strings.south, &textures->texture[S_N].img);
	textures->texture[S_N].addr = mlx_get_data_addr(textures->texture[S_N].img, &textures->texture[S_N].bpp, &textures->texture[S_N].line_length, &textures->texture[S_N].endian);
	if (textures->strings.ceiling)
	{
		xpm_image(game, (char *)textures->strings.ceiling, &textures->texture[C_N].img);
		textures->texture[C_N].addr = mlx_get_data_addr(textures->texture[C_N].img, &textures->texture[C_N].bpp, &textures->texture[C_N].line_length, &textures->texture[C_N].endian);
	}
	if (textures->strings.floor)
	{
		xpm_image(game, (char *)textures->strings.floor, &textures->texture[F_N].img);
		textures->texture[F_N].addr = mlx_get_data_addr(textures->texture[F_N].img, &textures->texture[F_N].bpp, &textures->texture[F_N].line_length, &textures->texture[F_N].endian);	
	}
}

void	parsing(char *path, t_game *game)
{
	int			index;

	init_game(game);
	validate_file(path, &game->file);
	get_file(path, &game->file);
	index = get_textures(&game->file, &game->textures, game);
	if (!collected_textures(&game->textures))
		errorer(game, 3, CANT_TXTR);
	get_map(game, &game->map, index);
	validate_map(&game->map, game);
	create_textures(game, &game->textures);
}
