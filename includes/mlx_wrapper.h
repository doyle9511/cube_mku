/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:55:42 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:05:42 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_WRAPPER_H
# define MLX_WRAPPER_H

/* mlx/mlx_wrapper.c */
void	*mlx_init_wrapper(void);
void	*mlx_new_window_wrapper(void *mlx_ptr, int width, \
		int height, char *title);
void	*mlx_new_image_wrapper(void *mlx_ptr, int width, int height);
int		mlx_hook_wrapper(void *win_ptr, int event, int mask, \
		int (*f)(), void *param);

#endif