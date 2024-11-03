/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:37:44 by ahashem           #+#    #+#             */
/*   Updated: 2024/11/03 15:22:33 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	correct_color(t_put_ray *p, t_ray_data *ray, t_game *game, int x)
{
	p->color = get_pixel_color_from_texture(ray->current_texture, \
		p->tex_x, p->tex_y);
	p->color = change_shade(p->color, ray->distance, p->dist_avg);
	pixel_put(&game->img, x, p->y++, p->color);
}

void	bigger_than_wh(t_ray_data *ray, t_game *game, int x, t_put_ray p)
{
	float	factor;
	int		start;
	int		temp;

	factor = ray->current_texture->height / ray->wall_h;
	start = ((int)ray->wall_h - WINDOW_H) / 2;
	temp = start;
	while ((start < ray->wall_h - temp) && p.y >= 0 && p.y < WINDOW_H)
	{
		p.tex_y = (int)(start * factor);
		start++;
		correct_color(&p, ray, game, x);
	}
}

void	smaller_than_wh(t_ray_data *ray, t_game *game, int x, t_put_ray p)
{
	int		i;
	int		clr;
	float	half_height;
	float	factor2;

	i = 0;
	clr = 0;
	half_height = (WINDOW_H - ray->wall_h) / 2.f;
	factor2 = ray->current_texture->height / ray->wall_h;
	while (i < p.y)
	{
		pixel_put(&game->img, x, i, game->textures.ceiling);
		i++;
	}
	while (p.y < WINDOW_H - half_height && p.y >= 0)
	{
		p.tex_y = (int)((p.y - half_height) * factor2);
		correct_color(&p, ray, game, x);
	}
	while (p.y < WINDOW_H)
	{
		clr = shade_floor(game->textures.floor, p.y);
		pixel_put(&game->img, x, p.y, clr);
		p.y++;
	}
}

void	draw_vertical_line(t_game *game, int x, t_ray_data *ray)
{
	t_put_ray	p;

	p.tex_y = 0;
	p.tex_x = (int)(ray->intercept * (ray->current_texture->width / 64));
	if (p.tex_x >= ray->current_texture->width)
		p.tex_x = p.tex_x - (p.tex_x / ray->current_texture->width) \
			* ray->current_texture->width;
	p.dist_avg = 1.f - ((ray->distance - MINIMUM) / (MAXIMUM - MINIMUM));
	p.color = 0;
	if (ray->wall_h < WINDOW_H)
	{
		p.y = (WINDOW_H - ray->wall_h) / 2;
		smaller_than_wh(ray, game, x, p);
	}
	else if (ray->wall_h > WINDOW_H)
	{
		p.y = 0;
		bigger_than_wh(ray, game, x, p);
	}
}
