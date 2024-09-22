/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:50:24 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 17:15:20 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	validate_file(char *path, t_file *file)
{
	char	*line;

	if (ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4) != 0)
		(write(2, USAGE, ft_strlen(USAGE)), exit(1));
	file->file_size = 1;
	file->file = NULL;
	file->fd = open(path, O_RDONLY);
	if (file->fd == -1)
		(write(2, FILE_404, ft_strlen(FILE_404)), exit(1));
	line = get_next_line(file->fd);
	if (!line)
		(write(2, EMPTY, ft_strlen(EMPTY)), exit(1));
	while (line)
	{
		file->file_size++;
		free(line);
		line = get_next_line(file->fd);
	}
	free(line);
	if (file->file_size < 9)
		(write(2, INVALID, ft_strlen(INVALID)), exit(1));
	close (file->fd);
	file->fd = -1;
}

void	get_file(char *path, t_file *file)
{
	int	i;

	file->fd = open(path, O_RDONLY);
	file->file = malloc(sizeof(char *) * file->file_size);
	if (!file->file)
		(write(2, INVALID, ft_strlen(INVALID)), exit(1));
	i = 0;
	while (i < file->file_size - 1)
		file->file[i++] = ft_strtrim(get_next_line(file->fd), "\n");
	file->file[i] = NULL;
	close(file->fd);
}
