/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 15:18:44 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/move.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x - game->player.dir_x * move_speed;
	new_y = game->player.pos_y - game->player.dir_y * move_speed;
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x - game->player.plane_x * move_speed;
	new_y = game->player.pos_y - game->player.plane_y * move_speed;
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_speed;

	move_speed = MOVE_SPEED;
	new_x = game->player.pos_x + game->player.plane_x * move_speed;
	new_y = game->player.pos_y + game->player.plane_y * move_speed;
	if (!is_wall(&game->map, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(&game->map, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

void	move_player(t_game *game)
{
	if (game->player.move_forward)
		move_forward(game);
	if (game->player.move_backward)
		move_backward(game);
	if (game->player.move_left)
		move_left(game);
	if (game->player.move_right)
		move_right(game);
}
