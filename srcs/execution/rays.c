/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:51:46 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/02 21:35:38 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.174533

void	draw(t_game *game, int center_x, int center_y, int colour)
{
    int x, y;

	int radius = 5;
    for (y = center_y - radius; y <= center_y + radius; y++)
        for (x = center_x - radius; x <= center_x + radius; x++)
            if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= radius * radius)
				pixel_put(&game->img, x, y, colour);
}

void rays(t_game *game)
{
	int dof = 0;
	float ra;
	float atan;
	float ry, rx;
	int yo, xo;
	int mx, my;

	ra = game->map.angle - (DR * 30);
	if (ra < 0)
		ra += (2 * PI);
	else if (ra > (2 * PI))
		ra -= (2 * PI);
	atan = -1 / tan(ra);
	if (ra > PI)
	{
		ry = (((int)(game->map.player_y * 64) >> 6) << 6) -0.0001;
		rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);
		yo = -64;
		xo = -yo * atan;
	}
	if (ra < PI)
	{
		ry = (((int)(game->map.player_y * 64) >> 6) << 6) + 64;
		rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);
		yo = 64;
		xo = -yo * atan;
	}
	if (ra == 0 || ra == PI)
	{
		ry = (game->map.player_y * 64);
		rx = (game->map.player_x * 64);
		dof = 8;
	}
	// printf("angle: %f\n", ra);
	printf("px: %f\npy: %f\n", (game->map.player_x * 64), (game->map.player_y * 64));
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		// printf("mx: %d\nmy: %d\n", mx, my);
		if (((mx > 0 && mx < game->map.width) && (my > 0 && my < game->map.height)) && game->map.map[my][mx] == WALL)
			dof = 8;
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	draw(game, rx, ry, 0x2a9df5);
}