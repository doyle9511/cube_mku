/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:50:36 by donghwi2          #+#    #+#             */
/*   Updated: 2025/04/26 17:01:20 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/utils.h"
#include "../includes/mlx_wrapper.h"

void	init_textures(t_game *game)
{
	int	i;

	game->tex_buf = malloc(sizeof(int *) * 4);
	if (!game->tex_buf)
		error_exit("Failed to allocate memory for textures");
	i = 0;
	while (i < 4)
	{
		game->tex_buf[i] = malloc(sizeof(int) * (TEX_WIDTH * TEX_HEIGHT));
		if (!game->tex_buf[i])
		{
			while (--i >= 0)
				free(game->tex_buf[i]);
			free(game->tex_buf);
			error_exit("Failed to allocate memory for textures");
		}
		i++;
	}
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init_wrapper();
	if (!game->mlx)
		error_exit("Failed to initialize MLX");
	game->win = mlx_new_window_wrapper(game->mlx, WIN_WIDTH, WIN_HEIGHT, \
		"cub3D");
	if (!game->win)
		error_exit("Failed to create window");
	game->img.img = mlx_new_image_wrapper(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		error_exit("Failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	init_textures(game);
}
