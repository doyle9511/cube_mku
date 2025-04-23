/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:50:36 by donghwi2          #+#    #+#             */
/*   Updated: 2025/04/17 21:54:41 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * 텍스처 버퍼 초기화
 * 텍스처 데이터를 저장할 2차원 배열 할당
 */
void	init_textures(t_game *game)
{
	int	i;

	game->tex_buf = malloc(sizeof(int *) * 4);// 텍스처 버퍼 메모리 할당
	if (!game->tex_buf)
		error_exit("Failed to allocate memory for textures");
	
	i = 0;
	while (i < 4)
	{
		game->tex_buf[i] = malloc(sizeof(int) * (TEX_WIDTH * TEX_HEIGHT));
		if (!game->tex_buf[i])
		{
			while (--i >= 0)
				free(game->tex_buf[i]);
			free(game->tex_buf);
			error_exit("Failed to allocate memory for textures");
		}
		i++;
	}
}

/**
 * MLX 윈도우 및 이미지 초기화
 * MLX 라이브러리를 사용하여 창과 그래픽 환경 설정
 */
void	init_window(t_game *game)
{
	game->mlx = mlx_init_wrapper();// MLX 초기화 - 그래픽 시스템에 연결
	if (!game->mlx)
		error_exit("Failed to initialize MLX");
	game->win = mlx_new_window_wrapper(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");// 윈도우 생성 - 지정된 크기의 창 생성
	if (!game->win)
		error_exit("Failed to create window");
	game->img.img = mlx_new_image_wrapper(game->mlx, WIN_WIDTH, WIN_HEIGHT);// 이미지 생성 - 화면에 그림을 그릴 이미지 버퍼 생성
	if (!game->img.img)
		error_exit("Failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,// 이미지 데이터 주소 가져오기 - 픽셀 단위로 그림을 그릴 수 있는 메모리 주소
			&game->img.line_length, &game->img.endian);
	init_textures(game);// 텍스처 버퍼 초기화
}
