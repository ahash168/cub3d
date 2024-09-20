/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:52:02 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/20 21:01:47 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	assign_texture(char *str, void **texture, t_game *game, int err_flag)
{
	char	**holder;
	int		height;
	int		width;
	int		fd;

	holder = ft_split(str, ' ');
	if (!holder[0] || !holder[1] || holder[2])
	{
		if (err_flag)
			write(2, INV_TXTR, ft_strlen(INV_TXTR));
		return (0);
	}
	fd = open(holder[1], O_RDONLY);
	if (fd == -1)
	{
		if (err_flag)
			write(2, TXTR_404, ft_strlen(TXTR_404));
		return (0);
	}
	close(fd);
	(*texture) = mlx_xpm_file_to_image(game->mlx, holder[1], &width, &height);
	if (!(*texture))
	{
		if (err_flag)
			write(2, XPM, ft_strlen(XPM));
		return (0);
	}
	free_array(holder);
	return (1);
}