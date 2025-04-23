/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:56:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * MLX 초기화 함수 래퍼
 * mlx_init: 그래픽 시스템을 초기화하고 연결
 */
void	*mlx_init_wrapper(void)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		error_exit("MLX initialization failed");
	return (mlx_ptr);
}

/**
 * 새 윈도우 생성 함수 래퍼
 * mlx_new_window: 지정된 크기와 제목으로 새 창 생성
 */
void	*mlx_new_window_wrapper(void *mlx_ptr, int width, int height, char *title)
{
	void	*win_ptr;

	win_ptr = mlx_new_window(mlx_ptr, width, height, title);
	if (!win_ptr)
		error_exit("MLX window creation failed");
	return (win_ptr);
}

/**
 * 새 이미지 생성 함수 래퍼
 * mlx_new_image: 지정된 크기로 새 이미지 생성
 */
void	*mlx_new_image_wrapper(void *mlx_ptr, int width, int height)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!img_ptr)
		error_exit("MLX image creation failed");
	return (img_ptr);
}

/**
 * 이벤트 훅 등록 함수 래퍼
 * mlx_hook: 특정 이벤트에 대한 콜백 함수 등록
 */
int	mlx_hook_wrapper(void *win_ptr, int event, int mask, int (*f)(), void *param)
{
	return (mlx_hook(win_ptr, event, mask, f, param));
}