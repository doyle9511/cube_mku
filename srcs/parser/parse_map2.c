/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:26:27 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 16:48:00 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

static int	hopping_texture_color_flag(int *i, char **lines)
{
	if (lines[*i] && (ft_strncmp(lines[*i], "NO ", 3) == 0
			|| ft_strncmp(lines[*i], "SO ", 3) == 0
			|| ft_strncmp(lines[*i], "WE ", 3) == 0
			|| ft_strncmp(lines[*i], "EA ", 3) == 0
			|| ft_strncmp(lines[*i], "F ", 2) == 0
			|| ft_strncmp(lines[*i], "C ", 2) == 0
			|| lines[*i][0] == '\0'))
		return (1);
	return (0);
}

int	find_map_dimensions(char **lines, t_game *game, int *start_line)
{
	int	i;

	i = 0;
	while (hopping_texture_color_flag(&i, lines))
		i++;
	*start_line = i;
	game->map.height = 0;
	while (lines[i])
	{
		game->map.height++;
		i++;
	}
	game->map.width = 0;
	i = *start_line;
	while (i < *start_line + game->map.height)
	{
		if (ft_strlen(lines[i]) > game->map.width)
			game->map.width = ft_strlen(lines[i]);
		i++;
	}
	return (0);
}

int	copy_map_data(char **lines, t_game *game, int start_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(lines[start_line + i]))
		{
			game->map.grid[i][j] = lines[start_line + i][j];
			j++;
		}
		while (j < game->map.width)
		{
			game->map.grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

int	read_map_file_part1(char *file_path, int *fd, char *buffer)
{
	int	bytes_read;

	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
	{
		print_error("Failed to open map file");
		return (-1);
	}
	bytes_read = read(*fd, buffer, 4095);
	if (bytes_read <= 0)
	{
		print_error("Failed to read map file or file is empty");
		close(*fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	return (0);
}

int	parse_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_line(game, line));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(game, line));
	return (0);
}
