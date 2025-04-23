/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/19 03:33:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * 메인 렌더링 루프 함수
 * mlx_loop의 콜백으로 등록되어 프레임마다 호출됨
 */
int	main_loop(t_game *game)
{
	move_player(game);
	rotate_player(game);
	render_frame(game);
	return (0);
}

/**
 * 이벤트 핸들러 등록 함수
 */
void	setup_hooks(t_game *game)
{
	mlx_hook_wrapper(game->win, EVENT_KEY_PRESS, 1L<<0, key_press, game);// KeyPress 이벤트
	mlx_hook_wrapper(game->win, EVENT_KEY_RELEASE, 1L<<1, key_release, game);// KeyRelease 이벤트
	mlx_hook_wrapper(game->win, EVENT_EXIT, 1L<<17, exit_game, game);// DestroyNotify 이벤트
}

/**
 * 프로그램 진입점
 * 인자를 검증하고 게임을 초기화한 후 메인 루프 시작
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3D [map_file.cub]");
		return (1);
	}
	init_game(&game);//게임 구조체 초기화
	if (parse_map(&game, argv[1]) == -1)//맵파일 파싱
	{
		free_resources(&game);
		return (1);
	}
	init_player(&game);//플레이어 초기 위치와 방향 설정
	init_window(&game);//MLX창과 이미지 버퍼 초기화
	if (load_textures(&game) == -1)//텍스쳐 이미지 로드
	{
		free_resources(&game);
		return (1);
	}
	setup_hooks(&game);//키보드 및 종료 이벤트 헨들러 등록

	//main_loop는 매 프레임마다 실행됨; 플레이어 [이동/회전] 상태에 따른 [위치/방향] 업데이트, 화면 렌더링
	mlx_loop_hook(game.mlx, main_loop, &game);// mlx_loop_hook: 화면이 갱신될 때마다 main_loop 함수 호출
	mlx_loop(game.mlx);//이벤트 루프 시작 (이 함수는 프로그램이 종료될 때까지 반환되지 않음)
	return (0);
}