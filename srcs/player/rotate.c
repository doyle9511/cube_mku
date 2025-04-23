/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/23 06:08:41 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 왼쪽으로 회전 (반시계 방향)
 */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	
	// 방향 벡터 회전
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	
	// 카메라 평면 벡터 회전 (방향 벡터와 수직 유지)
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

/**
 * 오른쪽으로 회전 (시계 방향)
 */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	
	// 방향 벡터 회전 (왼쪽 회전의 반대 방향)
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed)
		+ game->player.dir_y * cos(-rot_speed);
	
	// 카메라 평면 벡터 회전 (방향 벡터와 수직 유지)
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed)
		+ game->player.plane_y * cos(-rot_speed);
}

/**
 * 플레이어 회전 상태에 따라 방향 업데이트
 */
void	rotate_player(t_game *game)
{
	// 왼쪽으로 회전
	if (game->player.rotate_left)
		rotate_left(game);
	
	// 오른쪽으로 회전
	if (game->player.rotate_right)
		rotate_right(game);
}