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

void	free_resources(t_game *game)
{
	free_textures(game);
	free_texture_buffer(game);
	free_map(&game->map);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	#ifdef __linux__
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	#endif
	if (game->mlx)
		free(game->mlx);
}

int	exit_game(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
