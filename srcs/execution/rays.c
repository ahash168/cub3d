/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:51:46 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/10 19:40:56 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533
#define P2	PI/2
#define P3	3 * PI/2

// void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1;
// 	int sy = (y0 < y1) ? 1 : -1;
// 	int err = dx - dy;
// 	int e2;

// 	while (1)
// 	{
// 		// Draw the current pixel
// 		pixel_put(&game->img, x0, y0, color);

// 		// If the line has reached its endpoint, break out of the loop
// 		if (x0 == x1 && y0 == y1)
// 			break;

// 		// Store the error value before changing it
// 		e2 = 2 * err;

// 		// Adjust error and move the point horizontally or diagonally
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}

// 		// Adjust error and move the point vertically or diagonally
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// // void	draw(t_game *game, int center_x, int center_y, int colour)
// // {
// //     int x, y;

// // 	int radius = 5;
// //     for (y = center_y - radius; y <= center_y + radius; y++)
// //         for (x = center_x - radius; x <= center_x + radius; x++)
// //             if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= radius * radius)
// // 				draw_line(&game->img, x, y, colour);
// // }

// // float	distance(float px, float py, float rx, float ry)
// // {
// // 	return (sqrt((rx - px) * (rx - px)) + ((ry - py) * (ry - py)));
// // }

// // void rays(t_game *game)
// // {
// // 	int dof = 0;
// // 	float ra;
// // 	float atan;
// // 	float ntan;
// // 	float ry, rx;
// // 	int yo, xo;
// // 	int mx, my;

// // 	float hx = game->map.player_x;
// // 	float hy = game->map.player_y;
// // 	float disH = 1000000;
	
// // 	float vx = game->map.player_x;
// // 	float vy = game->map.player_y;
// // 	float disV = 1000000;
	
// // 	ra = game->map.angle;
// // 	if (ra < 0)
// // 		ra += (2 * PI);
// // 	else if (ra > (2 * PI))
// // 		ra -= (2 * PI);

// // 	//	HORIZONTAL
	
// // 	atan = -1 / tan(ra);
// // 	if (ra > PI)
// // 	{
// // 		ry = (((int)(game->map.player_y * 64) >> 6) << 6) - 0.0001;
// // 		rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);
// // 		yo = -64;
// // 		xo = -yo * atan;
// // 	}
// // 	if (ra < PI)
// // 	{
// // 		ry = (((int)(game->map.player_y * 64) >> 6) << 6) + 64;
// // 		rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);
// // 		yo = 64;
// // 		xo = -yo * atan;
// // 	}
// // 	if (ra == 0 || ra == PI)
// // 	{
// // 		ry = (game->map.player_y * 64);
// // 		rx = (game->map.player_x * 64);
// // 		dof = 8;
// // 	}
// // 	while (dof < 8)
// // 	{
// // 		mx = (int)rx >> 6;
// // 		my = (int)ry >> 6;
// // 		if (((mx >= 0 && mx < game->map.width) && (my >= 0 && my < game->map.height)) && game->map.map[my][mx] == WALL)
// // 		{
// // 			hx = rx;
// // 			hy = ry;
// // 			disH = distance(game->map.player_x, game->map.player_y, hx, hy);
// // 			dof = 8;
// // 		}
// // 		else
// // 		{
// // 			rx += xo;
// // 			ry += yo;
// // 			dof++;
// // 		}
// // 	}
		
// // 	// VERTICAL	

// // 	dof = 0;
// // 	ntan = -tan(ra);
// // 	if (ra > P2 && ra < P3)
// // 	{
// // 		rx = (((int)(game->map.player_x * 64) >> 6) << 6) - 0.0001;
// // 		ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
// // 		xo = -64;
// // 		yo = -xo * ntan;
// // 	}
// // 	if (ra < P2 || ra > P3)
// // 	{
// // 		rx = (((int)(game->map.player_x * 64) >> 6) << 6) + 64;
// // 		ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
// // 		xo = 64;
// // 		yo = -xo * ntan;
// // 	}
// // 	if (ra == 0 || ra == PI)
// // 	{
// // 		rx = (game->map.player_x * 64);
// // 		ry = (game->map.player_y * 64);
// // 		dof = 8;
// // 	}
// // 	while (dof < 8)
// // 	{
// // 		mx = (int)rx >> 6;
// // 		my = (int)ry >> 6;
// // 		if (((mx >= 0 && mx < game->map.width) && (my >= 0 && my < game->map.height)) && game->map.map[my][mx] == WALL)
// // 		{
// // 				vx = rx;
// // 				vy = ry;
// // 				disV = distance(game->map.player_x, game->map.player_y, vx, vy);
// // 				dof = 8;
// // 		}
// // 		else
// // 		{
// // 			rx += xo;
// // 			ry += yo;
// // 			dof++;
// // 		}
// // 	}
// // 	if (disH < disV)
// // 	{
// // 		rx = hx;
// // 		ry = hy;
// // 	}
// // 	else
// // 	{
// // 		rx = vx;
// // 		ry = vy;
// // 	}
// // 	// printf("mx: %d\nmy: %d\n", mx, my);
// // 	draw(game, rx, ry, 0x2a9df5);
// // }


























// void rays(t_game *game)
// {
//     int dof;
//     float ra;      // Ray angle
//     float atan, ntan;
//     float rx, ry;  // Horizontal ray positions
//     // float vx, vy;  // Vertical ray positions
//     int yo, xo;
//     int mx, my;
//     float dist_hor, dist_ver;  // Distance to horizontal and vertical intersections
// 	int r = 0;

//     // Initialize the ray angle
//     ra = game->map.angle - DR * 30;  // FOV typically around 60 degrees, DR is the ray delta angle
//     if (ra < 0)
//         ra += (2 * PI);
//     else if (ra > (2 * PI))
//         ra -= (2 * PI);
// 	while (r < 60)
// 	{
		
//     	// --- HORIZONTAL RAYCASTING ---
//     	dof = 0;
//     	atan = -1 / tan(ra);
//     	float hor_rx = 0, hor_ry = 0;  // Horizontal ray hit coordinates
//     	int hor_hit = 0;  // Flag to check if horizontal hit occurred
	
//     	if (ra > PI)  // Ray is facing up
//     	{
//     	    ry = (((int)(game->map.player_y * 64) >> 6) << 6) - 0.0001;  // Round down to nearest grid line
//     	    rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);  // Calculate rx based on ry
//     	    yo = -64;  // Step size for y when moving upward
//     	    xo = -yo * atan;  // Step size for x based on atan
//     	}
//     	else if (ra < PI)  // Ray is facing down
//     	{
//     	    ry = (((int)(game->map.player_y * 64) >> 6) << 6) + 64;  // Round up to nearest grid line
//     	    rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);  // Calculate rx based on ry
//     	    yo = 64;  // Step size for y when moving downward
//     	    xo = -yo * atan;  // Step size for x based on atan
//     	}
//     	else  // Ray is exactly horizontal
//     	{
//     	    ry = game->map.player_y * 64;
//     	    rx = game->map.player_x * 64;
//     	    dof = 100;  // Stop raycasting
//     	}
	
//     	while (dof < 100)  // Horizontal raycasting loop
//     	{
//     	    mx = (int)(rx) >> 6;  // Convert rx to map grid coordinates
//     	    my = (int)(ry) >> 6;  // Convert ry to map grid coordinates
	
//     	    if (mx >= 0 && mx < game->map.width && my >= 0 && my < game->map.height && game->map.map[my][mx] == WALL)
//     	    {
//     	        hor_rx = rx;  // Store horizontal hit coordinates
//     	        hor_ry = ry;
//     	        hor_hit = 1;  // Horizontal hit detected
//     	        dist_hor = sqrt((hor_rx - game->map.player_x * 64) * (hor_rx - game->map.player_x * 64) +
//     	                        (hor_ry - game->map.player_y * 64) * (hor_ry - game->map.player_y * 64));  // Calculate horizontal distance
//     	        dof = 100;  // Stop raycasting
//     	    }
//     	    else  // Move to the next grid cell
//     	    {
//     	        rx += xo;
//     	        ry += yo;
//     	        dof++;
//     	    }
//     	}
	
//     	// --- VERTICAL RAYCASTING ---
//     	dof = 0;
//     	ntan = -tan(ra);
//     	float vx = 0, vy = 0;  // Vertical ray hit coordinates
//     	int ver_hit = 0;  // Flag to check if vertical hit occurred
	
//     	if (ra > PI / 2 && ra < 3 * PI / 2)  // Ray is facing left
//     	{
//     	    rx = (((int)(game->map.player_x * 64) >> 6) << 6) - 0.0001;
//     	    ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
//     	    xo = -64;
//     	    yo = -xo * ntan;
//     	}
//     	else if (ra < PI / 2 || ra > 3 * PI / 2)  // Ray is facing right
//     	{
//     	    rx = (((int)(game->map.player_x * 64) >> 6) << 6) + 64;
//     	    ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
//     	    xo = 64;
//     	    yo = -xo * ntan;
//     	}
//     	else  // Ray is exactly vertical
//     	{
//     	    rx = game->map.player_x * 64;
//     	    ry = game->map.player_y * 64;
//     	    dof = 100;
//     	}
	
//     	while (dof < 100)  // Vertical raycasting loop
//     	{
//     	    mx = (int)(rx) >> 6;
//     	    my = (int)(ry) >> 6;
	
//     	    if (mx >= 0 && mx < game->map.width && my >= 0 && my < game->map.height && game->map.map[my][mx] == WALL)
//     	    {
//     	        vx = rx;  // Store vertical hit coordinates
//     	        vy = ry;
//     	        ver_hit = 1;  // Vertical hit detected
//     	        dist_ver = sqrt((vx - game->map.player_x * 64) * (vx - game->map.player_x * 64) +
//     	                        (vy - game->map.player_y * 64) * (vy - game->map.player_y * 64));  // Calculate vertical distance
//     	        dof = 100;
//     	    }
//     	    else
//     	    {
//     	        rx += xo;
//     	        ry += yo;
//     	        dof++;
//     	    }
//     	}
	
//     	// --- Compare Horizontal and Vertical Hits ---
//     	if (hor_hit && (!ver_hit || dist_hor < dist_ver))  // Horizontal hit is closer
//     	{
//     	    draw_line(game, game->map.player_x * 64, game->map.player_y * 64, hor_rx, hor_ry, 0x2a9df5);  // Draw horizontal hit
//     	}
//     	else if (ver_hit)  // Vertical hit is closer
//     	{
//     	    draw_line(game, game->map.player_x * 64, game->map.player_y * 64, vx, vy, 0x2a9df5);  // Draw vertical hit
//     	}
// 		ra += DR;
// 		if (ra < 0)
//     	    ra += (2 * PI);
//     	else if (ra > (2 * PI))
//     	    ra -= (2 * PI);
// 		r++;
// 	}
// }
