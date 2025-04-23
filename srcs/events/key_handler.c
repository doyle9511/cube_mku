/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/16 20:40:33 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 키 누름 이벤트 처리
 */
int	key_press(int keycode, t_game *game)
{
	printf("Key pressed: %d\n", keycode);
	// ESC 키: 게임 종료
	if (keycode == KEY_ESC)
		exit_game(game);
	
	// W 키: 앞으로 이동 시작
	else if (keycode == KEY_W)
		game->player.move_forward = 1;
	
	// S 키: 뒤로 이동 시작
	else if (keycode == KEY_S)
		game->player.move_backward = 1;
	
	// A 키: 왼쪽으로 이동 시작
	else if (keycode == KEY_A)
		game->player.move_left = 1;
	
	// D 키: 오른쪽으로 이동 시작
	else if (keycode == KEY_D)
		game->player.move_right = 1;
	
	// 왼쪽 화살표 키: 왼쪽으로 회전 시작
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 1;
	
	// 오른쪽 화살표 키: 오른쪽으로 회전 시작
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 1;
	
	return (0);
}

/**
 * 키 뗌 이벤트 처리
 */
int	key_release(int keycode, t_game *game)
{
	// W 키: 앞으로 이동 정지
	if (keycode == KEY_W)
		game->player.move_forward = 0;
	
	// S 키: 뒤로 이동 정지
	else if (keycode == KEY_S)
		game->player.move_backward = 0;
	
	// A 키: 왼쪽으로 이동 정지
	else if (keycode == KEY_A)
		game->player.move_left = 0;
	
	// D 키: 오른쪽으로 이동 정지
	else if (keycode == KEY_D)
		game->player.move_right = 0;
	
	// 왼쪽 화살표 키: 왼쪽으로 회전 정지
	else if (keycode == KEY_LEFT)
		game->player.rotate_left = 0;
	
	// 오른쪽 화살표 키: 오른쪽으로 회전 정지
	else if (keycode == KEY_RIGHT)
		game->player.rotate_right = 0;
	
	return (0);
}