/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:31:28 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 벽 충돌 검사
 */
static int	is_wall(t_map *map, double x, double y)
{
	// 맵 범위 체크
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	
	// 벽인지 확인 (1은 벽)
	if (map->grid[(int)y][(int)x] == '1')
		return (1);
	
	return (0);
}

/**
 * 앞으로 이동
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	
	// 방향 벡터를 따라 이동 위치 계산
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	
	// 벽 충돌 검사 후 이동
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * 뒤로 이동
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	
	// 방향 벡터의 반대 방향으로 이동 위치 계산
	new_x = game->player.pos_x - game->player.dir_x * move_speed;
	new_y = game->player.pos_y - game->player.dir_y * move_speed;
	
	// 벽 충돌 검사 후 이동
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * 왼쪽으로 이동 (시선 방향의 왼쪽, 즉 방향 벡터의 수직 벡터 방향)
 */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	
	// 방향 벡터의 왼쪽 수직 방향으로 이동 위치 계산
	new_x = game->player.pos_x - game->player.plane_x * move_speed;
	new_y = game->player.pos_y - game->player.plane_y * move_speed;
	
	// 벽 충돌 검사 후 이동
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * 오른쪽으로 이동 (시선 방향의 오른쪽, 즉 방향 벡터의 수직 벡터 반대 방향)
 */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	
	// 방향 벡터의 오른쪽 수직 방향으로 이동 위치 계산
	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;
	
	// 벽 충돌 검사 후 이동
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/**
 * 플레이어 이동 상태에 따라 위치 업데이트
 */
void	move_player(t_game *game)
{
	// 앞으로 이동
	if (game->player.move_forward)
		move_forward(game);
	
	// 뒤로 이동
	if (game->player.move_backward)
		move_backward(game);
	
	// 왼쪽으로 이동
	if (game->player.move_left)
		move_left(game);
	
	// 오른쪽으로 이동
	if (game->player.move_right)
		move_right(game);
}