/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 17:02:21 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

static int	validate_file_extension(char *file_path)
{
	char	*ext;

	ext = file_path + ft_strlen(file_path) - 4;
	if (ft_strlen(file_path) < 5 || ft_strncmp(ext, ".cub", 4) != 0)
	{
		print_error("Invalid file extension (should be .cub)");
		return (-1);
	}
	return (0);
}

static int	read_map_file(t_game *game, char *file_path)
{
	int		fd;
	char	buffer[4096];
	char	**lines;
	int		i;
	int		result;

	if (read_map_file_part1(file_path, &fd, buffer) == -1)
		return (-1);
	lines = ft_split(buffer, '\n');
	if (!lines)
		return (-1);
	i = 0;
	result = 0;
	while (lines[i] && result == 0)
	{
		result = parse_line(game, lines[i]);
		i++;
	}
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
	return (result);
}

static int	extract_map_data(t_game *game, char *file_content)
{
	char	**lines;
	int		start_line;

	lines = ft_split(file_content, '\n');
	if (!lines)
		return (-1);
	find_map_dimensions(lines, game, &start_line);
	game->map.grid = allocate_grid(game->map.height, game->map.width, 0, 0);
	if (!game->map.grid)
	{
		free_string_array(lines);
		return (-1);
	}
	copy_map_data(lines, game, start_line);
	free_string_array(lines);
	return (0);
}

static int	parse_map_part1(char *file_path, int *fd, char *buffer)
{
	int	bytes_read;

	if (validate_file_extension(file_path) == -1)
		return (-1);
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
	{
		print_error("Failed to open map file");
		return (-1);
	}
	bytes_read = read(*fd, buffer, 9999);
	if (bytes_read <= 0)
	{
		print_error("Failed to read map file or file is empty");
		close(*fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	close(*fd);
	return (0);
}

int	parse_map(t_game *game, char *file_path)
{
	char	buffer[10000];
	int		fd;

	if (parse_map_part1(file_path, &fd, buffer) == -1)
		return (-1);
	if (read_map_file(game, file_path) == -1)
		return (-1);
	if (extract_map_data(game, buffer) == -1)
	{
		print_error("Failed to extract map data");
		return (-1);
	}
	if (validate_map(game) == -1)
	{
		print_error("Invalid map");
		return (-1);
	}
	return (0);
}
