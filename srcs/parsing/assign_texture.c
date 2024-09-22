/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:52:02 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 21:09:07 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	texture_exiter(char **holder, t_game *game, char *m, int err_flag)
{
	free_array(holder);
	if (err_flag)
		errorer(game, 3, m);
	return (0);
}

int	assign_texture(char *str, char **texture, t_game *game, int err_flag)
{
	char	**holder;
	int		fd;

	holder = ft_split(str, ' ');
	if (!holder[0] || !holder[1] || holder[2])
		return (texture_exiter(holder, game, INV_TXTR, err_flag));
	if (!ft_strncmp(&holder[1][ft_strlen(holder[1]) - 4], ".xpm", 4))
	{
		fd = open(holder[1], O_RDONLY);
		if (fd == -1)
			return (texture_exiter(holder, game, TXTR_404, err_flag));
		close(fd);
		(*texture) = ft_strdup(holder[1]);
	}
	else
		return (texture_exiter(holder, game, INV_TXTR, err_flag));
	return (free_array(holder), 1);
}
