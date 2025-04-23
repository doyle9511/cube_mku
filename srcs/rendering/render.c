/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:29:59 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 바닥과 천장 그리기 (위쪽 절반은 천장, 아래쪽 절반은 바닥)
 */
void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		// 천장 그리기 (화면 상단 절반)
		if (y < WIN_HEIGHT / 2)
		{
			while (x < WIN_WIDTH)
			{
				my_mlx_pixel_put(&game->img, x, y, game->ceiling.value);
				x++;
			}
		}
		// 바닥 그리기 (화면 하단 절반)
		else
		{
			while (x < WIN_WIDTH)
			{
				my_mlx_pixel_put(&game->img, x, y, game->floor.value);
				x++;
			}
		}
		y++;
	}
}

/**
 * 한 프레임 렌더링
 */
int	render_frame(t_game *game)
{
	// 바닥과 천장 색상 그리기
	draw_floor_ceiling(game);
	
	// 레이캐스팅으로 벽 그리기
	raycasting(game);
	
	// mlx_put_image_to_window: 생성한 이미지를 윈도우에 출력
	// MLX 포인터, 윈도우 포인터, 이미지 포인터, x 좌표, y 좌표를 인자로 받음
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	
	return (0);
}