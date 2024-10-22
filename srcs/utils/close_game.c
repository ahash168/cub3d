/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:36:56 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/24 10:41:04 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_textures(t_txtr *pointers, void *mlx)
{
	if (pointers->ceiling)
		mlx_destroy_image(mlx, pointers->ceiling);
	if (pointers->east)
		mlx_destroy_image(mlx, pointers->east);
	if (pointers->north)
		mlx_destroy_image(mlx, pointers->north);
	if (pointers->west)
		mlx_destroy_image(mlx, pointers->west);
	if (pointers->south)
		mlx_destroy_image(mlx, pointers->south);
	if (pointers->floor)
		mlx_destroy_image(mlx, pointers->floor);
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
	destroy_textures(&game->textures.pointers, game->mlx);
	exit (flag);
}
