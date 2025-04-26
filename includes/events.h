/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:53:27 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 16:54:03 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

/* events/key_handler.c */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

/* events/exit_handler.c */
int		exit_game(t_game *game);
void	free_resources(t_game *game);

#endif