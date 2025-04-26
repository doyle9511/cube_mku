/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:58:55 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/move.h"
#include "../includes/rendering.h"
#include "../includes/parse.h"
#include "../includes/utils.h"
#include "../includes/events.h"
#include "../includes/mlx_wrapper.h"

int	main_loop(t_game *game)
{
	move_player(game);
	rotate_player(game);
	render_frame(game);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook_wrapper(game->win, EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook_wrapper(game->win, EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	mlx_hook_wrapper(game->win, EVENT_EXIT, 1L << 17, exit_game, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./cub3D [map_file.cub]");
		return (1);
	}
	init_game(&game);
	if (parse_map(&game, argv[1]) == -1)
	{
		free_resources(&game);
		return (1);
	}
	init_player(&game);
	init_window(&game);
	if (load_textures(&game) == -1)
	{
		free_resources(&game);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
