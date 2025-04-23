/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 17:38:41 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 레이 방향과 삼각함수 계산
 */
static void	init_ray_direction(t_game *game, t_ray *ray, int x)
{
	// 카메라 x 좌표 계산 (-1 ~ 1 사이의 값)
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	
	// 레이 방향 계산
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	
	// 현재 맵 좌표 (플레이어 위치의 정수 부분)
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
}

/**
 * 델타 거리와 이동 방향 계산
 */
static void	init_ray_delta_step(t_game *game, t_ray *ray)
{
	// 델타 거리 계산 (0으로 나누는 것을 방지하기 위한 처리)
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	
	// 이동 방향에 따른 step 값과 첫 번째 사이드 거리 계산
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) 
			* ray->delta_dist_x;
	}
}

/**
 * Y 방향 델타 거리와 이동 방향 계산
 */
static void	init_ray_delta_step_y(t_game *game, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) 
			* ray->delta_dist_y;
	}
}

/**
 * 레이캐스팅을 위한 초기값 설정
 */
void	init_ray(t_game *game, t_ray *ray, int x)
{
	// 레이 방향과 현재 맵 좌표 설정
	init_ray_direction(game, ray, x);
	
	// 델타 거리 및 이동 방향 계산
	init_ray_delta_step(game, ray);
	init_ray_delta_step_y(game, ray);
	
	// 초기값 설정
	ray->hit = 0;  // 벽을 만났는지 여부
	ray->side = 0; // 어느 면(X 또는 Y)에서 벽을 만났는지
}

/**
 * DDA 알고리즘을 사용하여 광선이 벽에 닿는 지점 찾기
 */
void	perform_dda(t_game *game, t_ray *ray)
{
	// DDA 알고리즘 수행 (벽을 만날 때까지 레이 진행)
	while (ray->hit == 0)
	{
		// X 방향이나 Y 방향 중 더 가까운 쪽으로 이동
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // X 면에서 만남
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Y 면에서 만남
		}
		
		// 벽을 만났는지 확인
		if (ray->map_y < 0 || ray->map_y >= game->map.height
			|| ray->map_x < 0 || ray->map_x >= game->map.width
			|| game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * 벽까지의 거리 계산
 */
void	calculate_wall_distance(t_ray *ray)
{
	// 벽까지의 거리 계산 (카메라 평면을 기준으로 한 수직 거리)
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

/**
 * 벽의 높이 계산
 */
void	calculate_wall_height(t_ray *ray)
{
	// 화면에 그릴 벽의 높이 계산
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	
	// 그릴 시작 y 좌표 계산
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	// 그릴 끝 y 좌표 계산
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/**
 * 메인 레이캐스팅 함수
 */
void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// 레이 초기화
		init_ray(game, &ray, x);
		
		// DDA 알고리즘으로 벽 찾기
		perform_dda(game, &ray);
		
		// 벽까지의 거리 계산
		calculate_wall_distance(&ray);
		
		// 화면에 그릴 벽의 높이 계산
		calculate_wall_height(&ray);
		
		// 벽의 텍스처 계산 및 그리기
		calculate_wall_texture(game, &ray);
		draw_wall_texture(game, &ray, x);
		
		x++;
	}
}