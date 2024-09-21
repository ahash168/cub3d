/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/20 21:52:25 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	x_button(t_game *game)
{
	(void) game;
	write(1, "Game over! You quit :p\n", 24);
	// close_game(game, 1);
	return (0);
}

// int	move(int keysym, t_game *game)
// {
// 	if (keysym == W)
// 		return (movement(game, -1, 0));
// 	if (keysym == A)
// 	{
// 		game->player = game->player_l;
// 		return (movement(game, 0, -1));
// 	}
// 	if (keysym == S)
// 		return (movement(game, 1, 0));
// 	if (keysym == D)
// 	{
// 		game->player = game->player_r;
// 		return (movement(game, 0, 1));
// 	}
// 	return (1);
// }

int	keypress(int keysym, t_game *game)
{
	(void) game;
	if (keysym == ESC)
	{
		write(1, "Game over! You quit :p\n", 24);
		// close_game(game, 1);
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
