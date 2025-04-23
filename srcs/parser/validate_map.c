/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/23 07:21:57 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 맵 내용이 유효한 문자로만 구성되어 있는지 확인
 */
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

/**
 * 수평 방향으로 벽 체크
 */
static int	check_horizontal_walls(t_map *map, int x, int y)
{
	// 좌우 벽 확인
	if (x - 1 < 0 || map->grid[y][x - 1] == ' ' 
		|| x + 1 >= map->width || map->grid[y][x + 1] == ' ')
		return (-1);
	return (0);
}

/**
 * 수직 방향으로 벽 체크
 */
static int	check_vertical_walls(t_map *map, int x, int y)
{
	// 상하 벽 확인
	if (y - 1 < 0 || map->grid[y - 1][x] == ' ' 
		|| y + 1 >= map->height || map->grid[y + 1][x] == ' ')
		return (-1);
	return (0);
}

/**
 * 대각선 방향으로 벽 체크
 */
static int	check_diagonal_walls(t_map *map, int x, int y)
{
	// 대각선 확인
	if (y - 1 < 0 || x - 1 < 0 || map->grid[y - 1][x - 1] == ' ' 
		|| y - 1 < 0 || x + 1 >= map->width || map->grid[y - 1][x + 1] == ' ' 
		|| y + 1 >= map->height || x - 1 < 0 || map->grid[y + 1][x - 1] == ' ' 
		|| y + 1 >= map->height || x + 1 >= map->width 
		|| map->grid[y + 1][x + 1] == ' ')
		return (-1);
	return (0);
}

/**
 * 맵이 벽으로 둘러싸여 있는지 확인 (빈 공간으로부터 맵 밖으로 나갈 수 없는지)
 */
static int	check_surrounding(t_map *map, int x, int y)
{
	// 맵 경계 체크
	if (x <= 0 || x >= map->width - 1 || y <= 0 || y >= map->height - 1)
		return (-1);
	
	// 빈 공간이 맵 경계 또는 다른 빈 공간과 맞닿아 있는지 확인
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

/**
 * 맵이 벽으로 둘러싸여 있는지 확인
 */
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

/**
 * 플레이어 위치가 정확히 한 개 있는지 확인
 */
int	check_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (strchr("NSEW", map->grid[i][j]))
			{
				player_count++;
				map->player_dir = map->grid[i][j];
			}
			j++;
		}
		i++;
	}
	
	if (player_count != 1)
	{
		print_error("Map must have exactly one player position");
		return (-1);
	}
	return (0);
}

/**
 * 모든 텍스처와 색상이 제대로 설정되었는지 확인
 */
static int	check_textures_and_colors(t_game *game)
{
	int	i;

	// 텍스처 확인
	for (i = 0; i < 4; i++)
	{
		printf("Texture %d path: %s\n", i, game->textures[i].path ? game->textures[i].path : "NULL");
		if (game->textures[i].path == NULL)
		{
			print_error("Missing texture path");
			return (-1);
		}
	}
	
	// 색상 확인
	if (game->floor.value == -1 || game->ceiling.value == -1)
	{
		print_error("Missing color information");
		return (-1);
	}
	
	return (0);
}

/**
 * 맵 유효성 검사 메인 함수
 */
int	validate_map(t_game *game)
{
	// 텍스처와 색상 확인
	if (check_textures_and_colors(game) == -1)
		return (-1);
	// 맵 내용 확인
	if (check_map_chars(&game->map) == -1)
	{
		print_error("Map contains invalid ch aracters");
		return (-1);
	}
	
	// 플레이어 확인
	if (check_player(&game->map) == -1)
		return (-1);
	
	// 벽 확인
	if (check_walls(&game->map) == -1)
	{
		print_error("Map must be surrounded by walls");
		return (-1);
	} 
	return (0);
}