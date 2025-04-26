/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:51:09 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"

void	*mlx_init_wrapper(void)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		error_exit("MLX initialization failed");
	return (mlx_ptr);
}

void	*mlx_new_window_wrapper(void *mlx_ptr, int width, \
		int height, char *title)
{
	void	*win_ptr;

	win_ptr = mlx_new_window(mlx_ptr, width, height, title);
	if (!win_ptr)
		error_exit("MLX window creation failed");
	return (win_ptr);
}

void	*mlx_new_image_wrapper(void *mlx_ptr, int width, int height)
{
	void	*img_ptr;

	img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!img_ptr)
		error_exit("MLX image creation failed");
	return (img_ptr);
}

int	mlx_hook_wrapper(void *win_ptr, int event, \
	int mask, int (*f)(), void *param)
{
	return (mlx_hook(win_ptr, event, mask, f, param));
}
