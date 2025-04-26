/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:47:20 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/move.h"
#include "../includes/utils.h"

void	init_game(t_game *game)
{
	int	i;

	memset(game, 0, sizeof(t_game));
	i = 0;
	while (i < 4)
	{
		game->textures[i].path = NULL;
		i++;
	}
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_dir = 0;
	game->floor.value = -1;
	game->ceiling.value = -1;
	game->tex_buf = NULL;
}

void	init_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (strchr("NSEW", game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				set_player_direction(game, game->map.grid[y][x]);
				game->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	set_ns_direction(t_game *game, char dir)
{
	game->player.dir_x = 0;
	if (dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	set_ew_direction(t_game *game, char dir)
{
	game->player.dir_y = 0;
	if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else
	{
		game->player.dir_x = -1;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	set_player_direction(t_game *game, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_ns_direction(game, dir);
	else if (dir == 'E' || dir == 'W')
		set_ew_direction(game, dir);
}
