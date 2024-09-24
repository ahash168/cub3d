/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/24 16:48:26 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		errorer(NULL, 1, USAGE);
	parsing(av[1], &game);
	// printf("player_x:	%f\nplayer_y:	%f\n", game.map.player_x, game.map.player_y);
	game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "cub3d");
	rendermap(&game);
	mlx_hook(game.window, 2, 0, move_player, &game);
	mlx_loop(game.mlx);
	close_game(&game, 0);
}
