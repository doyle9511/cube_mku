/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 17:03:09 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

static int	check_map_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
				&& map->grid[i][j] != 'N' && map->grid[i][j] != 'S'
				&& map->grid[i][j] != 'E' && map->grid[i][j] != 'W'
				&& map->grid[i][j] != ' ')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	check_player_util(t_map *map, int *player_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (strchr("NSEW", map->grid[i][j]))
			{
				(*player_count)++;
				map->player_dir = map->grid[i][j];
			}
			j++;
		}
		i++;
	}
}

int	check_player(t_map *map)
{
	int	player_count;

	player_count = 0;
	check_player_util(map, &player_count);
	if (player_count != 1)
	{
		print_error("Map must have exactly one player position");
		return (-1);
	}
	return (0);
}

static int	check_textures_and_colors(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path == NULL)
		{
			print_error("Missing texture path");
			return (-1);
		}
		i++;
	}
	if (game->floor.value == -1 || game->ceiling.value == -1)
	{
		print_error("Missing color information");
		return (-1);
	}
	return (0);
}

int	validate_map(t_game *game)
{
	if (check_textures_and_colors(game) == -1)
		return (-1);
	if (check_map_chars(&game->map) == -1)
	{
		print_error("Map contains invalid ch aracters");
		return (-1);
	}
	if (check_player(&game->map) == -1)
		return (-1);
	if (check_walls(&game->map) == -1)
	{
		print_error("Map must be surrounded by walls");
		return (-1);
	}
	return (0);
}
