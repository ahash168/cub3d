/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:50:24 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/22 20:47:38 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	validate_file(char *path, t_file *file)
{
	char	*line;

	if (ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4) != 0)
		errorer(NULL, 1, USAGE);
	file->file_size = 1;
	file->file = NULL;
	file->fd = open(path, O_RDONLY);
	if (file->fd == -1)
		errorer(NULL, 1, FILE_404);
	line = get_next_line(file->fd);
	if (!line)
		errorer(NULL, 1, EMPTY);
	while (line)
	{
		file->file_size++;
		free(line);
		line = get_next_line(file->fd);
	}
	free(line);
	if (file->file_size < 9)
		errorer(NULL, 1, INVALID);
	close (file->fd);
	file->fd = -1;
}

void	get_file(char *path, t_file *file)
{
	int	i;

	file->fd = open(path, O_RDONLY);
	file->file = malloc(sizeof(char *) * file->file_size);
	if (!file->file)
		errorer(NULL, 1, INVALID);
	i = 0;
	while (i < file->file_size - 1)
		file->file[i++] = ft_strtrim(get_next_line(file->fd), "\n");
	file->file[i] = NULL;
	close(file->fd);
}
