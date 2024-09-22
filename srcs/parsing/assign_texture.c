/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:52:02 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 17:32:08 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	assign_texture(char *str, char **texture, t_game *game, int err_flag)
{
	char	**holder;
	int		fd;

	(void)game;
	holder = ft_split(str, ' ');
	if (!holder[0] || !holder[1] || holder[2])
	{
		if (err_flag)
			write(2, INV_TXTR, ft_strlen(INV_TXTR));
		return (free_array(holder), 0);
	}
	if (!ft_strncmp(&holder[1][ft_strlen(holder[1]) - 4], ".xpm", 4))
	{
		fd = open(holder[1], O_RDONLY);
		if (fd == -1)
		{
			if (err_flag)
				write(2, TXTR_404, ft_strlen(TXTR_404));
			return (free_array(holder), 0);
		}
		close(fd);
		(*texture) = ft_strdup(holder[1]);
	}
	else
	{
		if (err_flag)
			write(2, INV_TXTR, ft_strlen(INV_TXTR));
		return (free_array(holder), 0);
	}
	return (free_array(holder), 1);
}
