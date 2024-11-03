/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:37:44 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 14:34:35 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	change_shade(int colour, float dist, float avg)
{
	float			shade_factor;
	t_trgb			new;

	shade_factor = (dist <= MINIMUM) * 1.f + (dist >= MAXIMUM) * 0.f;
	if (dist > MINIMUM && dist < MAXIMUM)
	{
		shade_factor = avg;
		if (shade_factor < 0.0f)
			shade_factor = 0.0f;
		if (shade_factor > 1.0f)
			shade_factor = 1.0f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	shade_floor(int colour, int y)
{
	float	shade_factor;
	t_trgb	new;
	int		check;

	check = WINDOW_H - y;
	if (check <= MINIMUMF)
		shade_factor = 1.f;
	else if (check >= MAXIMUMF)
		shade_factor = 0.f;
	else
	{
		shade_factor = 1.f - (((check) - MINIMUMF) / (MAXIMUMF - MINIMUMF));
		if (shade_factor < 0.f)
			shade_factor = 0.f;
		if (shade_factor > 1.f)
			shade_factor = 1.f;
	}
	new.trgb = colour;
	new.r = ((new.trgb >> 16) & 0xFF) * shade_factor;
	new.g = ((new.trgb >> 8) & 0xFF) * shade_factor;
	new.b = (new.trgb & 0xFF) * shade_factor;
	new.shaded = (new.trgb & 0xFF000000) | (new.r << 16) | (new.g << 8) | new.b;
	return (new.shaded);
}

int	get_pixel_color_from_texture(t_data *texture, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}


void	draw_vertical_line(t_game *game, int x, t_ray_data *ray)
{
	int		y;
	int		i;
	int		tex_x;
	int		tex_y;
	float	dist_max_min_avg;
	float	half_height;
	float	factor2;
	int		color;
	int		clr;
	float	factor;
	int		start;
	int		temp;

	factor = ray->current_texture->height/ ray->wall_h;
	start = ((int)ray->wall_h - WINDOW_H) / 2;
	temp = start;
	color = 0;
	clr = 0;
	y = 0;
	i = 0;
	dist_max_min_avg = 1.f - ((ray->distance - MINIMUM) / (MAXIMUM - MINIMUM));
	tex_y = 0;
	tex_x = (int)(ray->intercept * (ray->current_texture->width / 64));
	if (tex_x >= ray->current_texture->width)
		tex_x = tex_x - (tex_x / ray->current_texture->width) * ray->current_texture->width;
	if (ray->wall_h < WINDOW_H)
	{
		half_height = (WINDOW_H - ray->wall_h) / 2.f;
		factor2 = ray->current_texture->height/ ray->wall_h;
		y = (WINDOW_H - ray->wall_h) / 2;
		while (i < y)
		{
			pixel_put(&game->img, x, i, game->textures.ceiling);
			i++;
		}
		while (y < WINDOW_H - half_height && y >= 0)
		{
			tex_y = (int)((y - half_height) * factor2);
			color = get_pixel_color_from_texture(ray->current_texture, tex_x, tex_y);
			color = change_shade(color, ray->distance, dist_max_min_avg);
			pixel_put(&game->img, x, y++, color);
		}
		while (y < WINDOW_H)
		{
			clr = shade_floor(game->textures.floor, y);
			pixel_put(&game->img, x, y, clr);
			y++;
		}
	}
	else if (ray->wall_h > WINDOW_H)
	{
		y = 0;
		while ((start < ray->wall_h - temp) && y >= 0 && y < WINDOW_H)
		{
			tex_y = (int)(start++ * factor);
			color = get_pixel_color_from_texture(ray->current_texture, tex_x, tex_y);
			color = change_shade(color, ray->distance, dist_max_min_avg);
			pixel_put(&game->img, x, y++, color);
		}
	}
}
