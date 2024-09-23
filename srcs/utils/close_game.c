/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:36:56 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/23 19:42:42 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	// if (game->window && game->mlx)
	// 	mlx_destroy_window(game->mlx, game->window);
	exit (flag);
}
