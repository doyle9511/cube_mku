/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:59:23 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 15:51:06 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/move.h"

static int	check_horizontal_walls(t_map *map, int x, int y)
{
	if (x - 1 < 0 || map->grid[y][x - 1] == ' '
		|| x + 1 >= map->width || map->grid[y][x + 1] == ' ')
		return (-1);
	return (0);
}

static int	check_vertical_walls(t_map *map, int x, int y)
{
	if (y - 1 < 0 || map->grid[y - 1][x] == ' '
		|| y + 1 >= map->height || map->grid[y + 1][x] == ' ')
		return (-1);
	return (0);
}

static int	check_diagonal_walls(t_map *map, int x, int y)
{
	if (y - 1 < 0 || x - 1 < 0 || map->grid[y - 1][x - 1] == ' '
		|| y - 1 < 0 || x + 1 >= map->width || map->grid[y - 1][x + 1] == ' '
		|| y + 1 >= map->height || x - 1 < 0 || map->grid[y + 1][x - 1] == ' '
		|| y + 1 >= map->height || x + 1 >= map->width
		|| map->grid[y + 1][x + 1] == ' ')
		return (-1);
	return (0);
}

static int	check_surrounding(t_map *map, int x, int y)
{
	if (x <= 0 || x >= map->width - 1 || y <= 0 || y >= map->height - 1)
		return (-1);
	if (map->grid[y][x] == '0' || strchr("NSEW", map->grid[y][x]))
	{
		if (check_horizontal_walls(map, x, y) == -1)
			return (-1);
		if (check_vertical_walls(map, x, y) == -1)
			return (-1);
		if (check_diagonal_walls(map, x, y) == -1)
			return (-1);
	}
	return (0);
}

int	check_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == '0' || strchr("NSEW", map->grid[i][j]))
			{
				if (check_surrounding(map, j, i) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
