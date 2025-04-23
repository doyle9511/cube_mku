/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/17 21:25:22 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 벽의 텍스처 위치 계산 및 텍스처 x 좌표 결정
 */
void	calculate_wall_texture(t_game *game, t_ray *ray)
{
	// 벽 텍스처의 정확한 충돌 지점 계산
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	
	// 소수 부분만 사용
	ray->wall_x -= floor(ray->wall_x);
	
	// 텍스처 x 좌표 계산
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	
	// x 방향으로 이동 중일 때 텍스처 반전 처리
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	
	// 텍스처 y 스텝 계산 (텍스처를 벽 높이에 맞게 스케일링)
	ray->tex_step = 1.0 * TEX_HEIGHT / ray->line_height;
	
	// 텍스처의 시작 위치 계산
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
}

/**
 * 텍스처 인덱스 결정 (벽의 방향에 따라 다른 텍스처 사용)
 */
static int	get_texture_index(t_ray *ray)
{
	// 벽의 방향에 따라 텍스처 선택
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (0); // 북쪽 텍스처
		else
			return (1); // 남쪽 텍스처
	}
	else
	{
		if (ray->step_y > 0)
			return (2); // 동쪽 텍스처
		else
			return (3); // 서쪽 텍스처
	}
}

/**
 * 텍스처를 사용하여 벽 그리기
 */
void	draw_wall_texture(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	int		tex_index;
	int		color;

	// 사용할 텍스처 결정
	tex_index = get_texture_index(ray);
	
	// 벽 높이만큼 세로로 그리기
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// 텍스처의 y 좌표 계산
		tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		ray->tex_pos += ray->tex_step;
		
		// 텍스처에서 색상 가져오기
		color = game->tex_buf[tex_index][TEX_HEIGHT * tex_y + ray->tex_x];
		
		// // 측면인 경우 색상 어둡게 처리
		// if (ray->side == 1)
		// 	color = (color >> 1) & 8355711; // 색상을 절반으로 어둡게
		
		// 픽셀 그리기
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}