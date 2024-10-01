/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/01 10:48:06 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game	game;

    if (ac != 2)
        errorer(NULL, 1, USAGE);
    parsing(av[1], &game);
    game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "cub3d");
	rendermap(&game);
    mlx_hook(game.window, 2, 1L << 0, &keypress, &game);
	mlx_hook(game.window, 17, 1L << 2, &x_button, &game);
    mlx_loop(game.mlx);
	close_game(&game, 0);
    return (0);
}
