/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:51:46 by tabadawi          #+#    #+#             */
/*   Updated: 2024/10/09 20:17:03 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define DR	0.0174533
#define P2	PI/2
#define P3	3 * PI/2

void	draw_vertical_line(t_game *game, int x, int h, int window_height, int color)
{
	int	y;

	// Start drawing from the bottom of the window
	y = (window_height - h) / 2;
	while ((y <= window_height - ((window_height - h ) / 2)) && y >= 0)
	{
		pixel_put(&game->img, x, y, color);
		// mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
		y++;
	}
}


void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		pixel_put(&game->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

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

    int dof;
    float ra;      // Ray angle
    float atan, ntan;
    float rx, ry;  // Horizontal ray positions
    // float vx, vy;  // Vertical ray positions
	double offset;
	offset  =  (60.0 / 1920.0) * (PI / 180.0);
	// printf("offset: %f\n", offset);
	float f_distance;
    int yo, xo;
    int mx, my;
    float dist_hor, dist_ver;  // Distance to horizontal and vertical intersections
	int r = 0;

    // Initialize the ray angle
    ra = game->map.angle - (DR * 30);  // FOV typically around 60 degrees, DR is the ray delta angle
    if (ra < 0)
        ra += (2 * PI);
    else if (ra > (2 * PI))
        ra -= (2 * PI);

	// int counter = 0;
	while (r < 1920)
	{
		// if (++counter == 2) {
			// ra += offset;
			// if (ra < 0)
			// 	ra += (2 * PI);
			// else if (ra > (2 * PI))
			// 	ra -= (2 * PI);
		// 	r++;
		// 	break;
		// }

    	// --- HORIZONTAL RAYCASTING ---
    	dof = 0;
    	atan = -1 / tan(ra);
    	float hx = 0, hy = 0;  // Horizontal ray hit coordinates
    	int hor_hit = 0;  // Flag to check if horizontal hit occurred
	
    	if (ra > PI)  // Ray is facing up
    	{
    	    ry = (((int)(game->map.player_y * 64) / 64) * 64) /*- 0.0001*/;  // Round down to nearest grid line
			rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);  // Calculate rx based on ry
    	    yo = -64;  // Step size for y when moving upward
    	    xo = -yo * atan;  // Step size for x based on atan
    	}
    	else if (ra < PI)  // Ray is facing down
    	{
    	    ry = (((int)(game->map.player_y * 64) / 64) * 64) /*+ 64*/;  // Round up to nearest grid line
    	    rx = ((game->map.player_y * 64) - ry) * atan + (game->map.player_x * 64);  // Calculate rx based on ry
    	    yo = 64;  // Step size for y when moving downward
    	    xo = -yo * atan;  // Step size for x based on atan
    	}
    	else  // Ray is exactly horizontal
    	{
    	    ry = game->map.player_y * 64;
    	    rx = game->map.player_x * 64;
    	    dof = 100;  // Stop raycasting
    	}
	
    	while (dof < 100)  // Horizontal raycasting loop
    	{
    	    mx = (int)(rx) >> 6;  // Convert rx to map grid coordinates
    	    my = (int)(ry) >> 6;  // Convert ry to map grid coordinates

			// printf("(%d, %d) -> ", mx, my);
			
    	    if (mx >= 0 && mx < game->map.width && my >= 0 && my < game->map.height && game->map.map[my][mx] == WALL)
    	    {
    	        hx = rx;  // Store horizontal hit coordinates
    	        hy = ry;
    	        hor_hit = 1;  // Horizontal hit detected
    	        dist_hor = sqrt((hx - game->map.player_x * 64) * (hx - game->map.player_x * 64) +
    	                        (hy - game->map.player_y * 64) * (hy - game->map.player_y * 64));  // Calculate horizontal distance
    	        dof = 100;  // Stop raycasting
    	    }
    	    else  // Move to the next grid cell
    	    {
    	        rx += xo;
    	        ry += yo;
    	        dof++;
    	    }
    	}
	
    	// --- VERTICAL RAYCASTING ---
    	dof = 0;
    	ntan = -tan(ra);
    	float vx = 0, vy = 0;  // Vertical ray hit coordinates
    	int ver_hit = 0;  // Flag to check if vertical hit occurred
	
    	if (ra > PI / 2 && ra < 3 * PI / 2)  // Ray is facing left
    	{
    	    rx = (((int)(game->map.player_x * 64) / 64) * 64) /*- 0.0001*/;
    	    ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
    	    xo = -64;
    	    yo = -xo * ntan;
    	}
    	else if (ra < PI / 2 || ra > 3 * PI / 2)  // Ray is facing right
    	{
    	    rx = (((int)(game->map.player_x * 64) / 64) * 64) /*+ 64*/;
    	    ry = ((game->map.player_x * 64) - rx) * ntan + (game->map.player_y * 64);
    	    xo = 64;
    	    yo = -xo * ntan;
    	}
    	else  // Ray is exactly vertical
    	{
    	    rx = game->map.player_x * 64;
    	    ry = game->map.player_y * 64;
    	    dof = 100;
    	}
	
    	while (dof < 100)  // Vertical raycasting loop
    	{
    	    mx = (int)(rx) >> 6;
    	    my = (int)(ry) >> 6;
	
    	    if (mx >= 0 && mx < game->map.width && my >= 0 && my < game->map.height && game->map.map[my][mx] == WALL)
    	    {
    	        vx = rx;  // Store vertical hit coordinates
    	        vy = ry;
    	        ver_hit = 1;  // Vertical hit detected
    	        dist_ver = sqrt((vx - game->map.player_x * 64) * (vx - game->map.player_x * 64) +
    	                        (vy - game->map.player_y * 64) * (vy - game->map.player_y * 64));  // Calculate vertical distance
    	        dof = 100;
    	    }
    	    else
    	    {
    	        rx += xo;
    	        ry += yo;
    	        dof++;
    	    }
    	}

    	// --- Compare Horizontal and Vertical Hits ---
    	if (hor_hit && (!ver_hit || dist_hor < dist_ver))
		{
			// printf("H: h_hit %d, v_hit %d\nh_dist %f, v_dist %f\n", hor_hit, ver_hit, dist_hor, dist_ver);
			rx = hx;
			// hx -= xo;
			// hy -= yo;
			f_distance = dist_hor;
		float line_h = (64 * 600) / f_distance;
		if (line_h > 600)
			line_h = 600;
		draw_vertical_line(game, rx * 64, line_h, 1080, 0xf5428a);

    	    // draw_line(game, game->map.player_x * 64, game->map.player_y * 64, hx, hy, 0x2a9df5);  // Draw horizontal hit
		}  // Horizontal hit is closer

    	else if (ver_hit)  // Vertical hit is closer
		{
			// printf("V: h_hit %d, v_hit %d\nh_dist %f, v_dist %f\n", hor_hit, ver_hit, dist_hor, dist_ver);
			rx = vx;
			// vx -= xo;
			// vy -= yo;
			f_distance = dist_ver;
		float line_h = (64 * 20) / f_distance;
		if (line_h > 20)
			line_h = 20;
		draw_vertical_line(game, rx * 64, line_h, 1080, 0x2a9df5);
	
    	    //  draw_line(game, game->map.player_x * 64, game->map.player_y * 64, vx, vy, 0x2a9df5);  // Draw vertical hit
		}

		
		ra += offset;
		if (ra < 0)
    	    ra += (2 * PI);
    	else if (ra > (2 * PI))
    	    ra -= (2 * PI);
		r++;
	}
}
