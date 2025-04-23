/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:31:02 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 이미지 버퍼에 픽셀 색상 설정
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	// 유효한 좌표 범위인지 확인
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	
	// 특정 픽셀의 메모리 주소 계산
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	
	// 해당 메모리 주소에 색상 값 저장
	*(unsigned int *)dst = color;
}

/**
 * 수직선 그리기
 */
void	draw_line(t_game *game, int x, t_ray *ray)
{
	int	y;
	int	color;

	// 사용할 색상 결정
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = 0xFF0000; // 빨강 (북쪽 벽)
		else
			color = 0x00FF00; // 초록 (남쪽 벽)
	}
	else
	{
		if (ray->step_y > 0)
			color = 0x0000FF; // 파랑 (동쪽 벽)
		else
			color = 0xFFFF00; // 노랑 (서쪽 벽)
	}
	
	// 측면인 경우 색상 어둡게 처리
	if (ray->side == 1)
		color = color / 2;
	
	// 벽 그리기
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}