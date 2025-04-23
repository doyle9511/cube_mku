/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/17 21:50:27 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * 게임 구조체 초기화
 * 모든 변수를 0으로 초기화하고 기본값 설정
 */
void	init_game(t_game *game)
{
	int	i;

	memset(game, 0, sizeof(t_game));// 모든 메모리를 0으로 초기화
	i = 0;
	while (i < 4)// 텍스처 배열 초기화
	{
		game->textures[i].path = NULL;
		i++;
	}
	game->map.grid = NULL;// 맵 구조체 초기화
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_dir = 0;
	game->floor.value = -1;// 색상 구조체 초기화
	game->ceiling.value = -1;
	game->tex_buf = NULL;// 텍스처 버퍼 초기화 (나중에 메모리 할당)
}

/**
 * 플레이어 위치 및 방향 초기화
 * 맵에서 플레이어 시작 위치와 방향을 찾아 설정
 */
void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (strchr("NSEW", game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				set_player_direction(game, game->map.grid[y][x]);
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

/**
 * 북쪽과 남쪽 방향 설정
 */
static void	set_ns_direction(t_game *game, char dir)
{
	game->player.dir_x = 0;
	if (dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

/**
 * 동쪽과 서쪽 방향 설정
 */
static void	set_ew_direction(t_game *game, char dir)
{
	game->player.dir_y = 0;
	if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.dir_x = -1;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

/**
 * 플레이어의 방향과 카메라 평면 설정
 */
void	set_player_direction(t_game *game, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_ns_direction(game, dir);
	else if (dir == 'E' || dir == 'W')
		set_ew_direction(game, dir);
}
