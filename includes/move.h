/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:17:22 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:04:32 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

typedef struct s_map	t_map;
typedef struct s_game	t_game;

int		is_wall(t_map *map, double x, double y);
/* player/move.c */
void	move_player(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/* player/rotate.c */
void	rotate_player(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	set_player_direction(t_game *game, char dir);
#endif