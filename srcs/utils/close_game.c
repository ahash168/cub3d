/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:36:56 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/30 15:26:34 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_texture(t_data *texture, t_data door, void *mlx)
{
	if (texture[N_N].img)
		mlx_destroy_image(mlx, texture[N_N].img);
	if (texture[E_N].img)
		mlx_destroy_image(mlx, texture[E_N].img);
	if (texture[W_N].img)
		mlx_destroy_image(mlx, texture[W_N].img);
	if (texture[S_N].img)
		mlx_destroy_image(mlx, texture[S_N].img);
	if (texture[C_N].img)
		mlx_destroy_image(mlx, texture[C_N].img);
	if (texture[F_N].img)
		mlx_destroy_image(mlx, texture[F_N].img);
	if (door.img)
		mlx_destroy_image(mlx, door.img);
}

int	close_game(t_game *game, int flag)
{
	if (game->file.file)
		free_array(game->file.file);
	if (game->map.map)
		free_array(game->map.map);
	ft_free(game->textures.strings.north);
	ft_free(game->textures.strings.east);
	ft_free(game->textures.strings.west);
	ft_free(game->textures.strings.south);
	ft_free(game->textures.strings.ceiling);
	ft_free(game->textures.strings.floor);
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	destroy_texture(game->textures.texture, game->textures.door, game->mlx);
	destroy_images(game);
	exit (flag);
}
