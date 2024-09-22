/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 20:39:50 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_game(t_game *game, int flag)
{
	(void) game;
	// mlx_destroy_window(game->mlx, game->window);
	exit (flag);
}

int	x_button(t_game *game)
{
	(void) game;
	write(1, "Game over! You quit :p\n", 24);
	close_game(game, 1);
	return (0);
}

int	keypress(int keysym, t_game *game)
{
	(void) game;
	if (keysym == ESC)
	{
		write(1, "Game over! You quit :p\n", 24);
		close_game(game, 1);
		return (0);
	}
	else
	{
		write(1, "moooove\n", 9);
		// movement move()
		return (0);
	}
	return (0);
}
