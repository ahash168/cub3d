/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/14 13:18:47 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game	game;

    if (ac != 2)
        errorer(NULL, 1, USAGE);
    parsing(av[1], &game);
    game.window = mlx_new_window(game.mlx, 1920, 1080, "cub3d");
	rendermap(&game);
    mlx_hook(game.window, 2, 1L << 0, &keypress, &game);
    mlx_hook(game.window, 3, 1L << 1, &keyrelease, &game);
	mlx_hook(game.window, 17, 1L << 2, &x_button, &game);
	mlx_loop_hook(game.mlx, loops, &game);
    mlx_loop(game.mlx);
	close_game(&game, 0);
    return (0);
}
