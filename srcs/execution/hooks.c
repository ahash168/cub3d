/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:46:57 by ahashem           #+#    #+#             */
/*   Updated: 2024/10/01 10:51:20 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	x_button(t_game *game)
{
	(void) game;
	write(1, "Game over! You quit :p\n", 24);
	close_game(game, 0);
	return (0);
}

int	keypress(int keysym, t_game *game)
{
	if (keysym == ESC)
		close_game(game, 0);
	if (keysym == LEFT || keysym == RIGHT)
	{
		rotate_player(keysym, game);
		return (0);
	}
	if (keysym == W || keysym == A || keysym == S || keysym == D)
	{
		move_player(keysym, game);
		return (0);
	}
	return (0);
}
