/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:51:46 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/03 22:06:40 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.174533
#define P2	PI/2
#define P3	3 * PI/2

void	draw(t_game *game, int center_x, int center_y, int colour)
{
    int x, y;

	int radius = 5;
    for (y = center_y - radius; y <= center_y + radius; y++)
        for (x = center_x - radius; x <= center_x + radius; x++)
            if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= radius * radius)
				pixel_put(&game->img, x, y, colour);
}

float	distance(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px)) + ((ry - py) * (ry - py)));
}

void rays(t_game *game)
{
	int dof = 0;
	float ra;
	float atan;
	float ntan;
	float ry, rx;
	int yo, xo;
	int mx, my;

	float hx = game->map.player_x;
	float hy = game->map.player_y;
	float disH = 1000000;
	
	float vx = game->map.player_x;
	float vy = game->map.player_y;
	float disV = 1000000;
	
	ra = game->map.angle;
	if (ra < 0)
		ra += (2 * PI);
	else if (ra > (2 * PI))
		ra -= (2 * PI);

	//	HORIZONTAL
	
	atan = -1 / tan(ra);
	if (ra > PI)
	{
		ry = (((int)(game->map.player_y * 64) >> 6) << 6) - 0.0001;
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
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		if (((mx >= 0 && mx < game->map.width) && (my >= 0 && my < game->map.height)) && game->map.map[my][mx] == WALL)
		{
			hx = rx;
			hy = ry;
			disH = distance(game->map.player_x, game->map.player_y, hx, hy);
			dof = 8;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
		
	// VERTICAL	

	dof = 0;
	ntan = -tan(ra);
	if (ra > P2 && ra < P3)
	{
		rx = (((int)(game->map.player_x * 64) >> 6) << 6) - 0.0001;
		ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
		xo = -64;
		yo = -xo * ntan;
	}
	if (ra < P2 || ra > P3)
	{
		rx = (((int)(game->map.player_x * 64) >> 6) << 6) + 64;
		ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
		xo = 64;
		yo = -xo * ntan;
	}
	if (ra == 0 || ra == PI)
	{
		rx = (game->map.player_x * 64);
		ry = (game->map.player_y * 64);
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		if (((mx >= 0 && mx < game->map.width) && (my >= 0 && my < game->map.height)) && game->map.map[my][mx] == WALL)
		{
				vx = rx;
				vy = ry;
				disV = distance(game->map.player_x, game->map.player_y, vx, vy);
				dof = 8;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof++;
		}
	}
	if (disH < disV)
	{
		rx = hx;
		ry = hy;
	}
	else
	{
		rx = vx;
		ry = vy;
	}
	// printf("mx: %d\nmy: %d\n", mx, my);
	draw(game, rx, ry, 0x2a9df5);
}