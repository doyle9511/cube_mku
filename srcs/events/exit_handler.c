/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 17:42:57 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 텍스처 메모리 해제
 */
static void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].path)
			free(game->textures[i].path);
		if (game->textures[i].img.img)
			mlx_destroy_image(game->mlx, game->textures[i].img.img);
		i++;
	}
}

/**
 * 맵 그리드 메모리 해제
 */
void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

/**
 * 텍스처 버퍼 메모리 해제
 */
static void	free_texture_buffer(t_game *game)
{
	int	i;

	if (!game->tex_buf)
		return ;
	
	i = 0;
	while (i < 4)
	{
		if (game->tex_buf[i])
			free(game->tex_buf[i]);
		i++;
	}
	free(game->tex_buf);
	game->tex_buf = NULL;
}

/**
 * 모든 리소스 해제
 */
void	free_resources(t_game *game)
{
	// 텍스처 메모리 해제
	free_textures(game);
	
	// 텍스처 버퍼 메모리 해제
	free_texture_buffer(game);
	
	// 맵 그리드 메모리 해제
	free_map(&game->map);
	
	// 이미지 메모리 해제
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	
	// 윈도우 메모리 해제
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	
	// MLX 메모리 해제 (일부 시스템에서만 필요)
	#ifdef __linux__
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	#endif
	
	// MLX 포인터 메모리 해제
	if (game->mlx)
		free(game->mlx);
}

/**
 * 게임 종료 함수 (X 버튼 클릭 또는 ESC 키 누름)
 */
int	exit_game(t_game *game)
{
	// 모든 리소스 해제
	free_resources(game);
	
	// 프로그램 종료
	exit(0);
	return (0);
}