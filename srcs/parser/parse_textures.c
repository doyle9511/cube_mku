/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 17:02:35 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"

static void	copy_texture_row(t_game *game, int index, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < game->textures[index].img.width)
	{
		color = *(unsigned int *)(game->textures[index].img.addr
				+ (y * game->textures[index].img.line_length
					+ x * (game->textures[index].img.bits_per_pixel / 8)));
		game->tex_buf[index][y * TEX_WIDTH + x] = color;
		x++;
	}
}

void	copy_texture_to_buffer(t_game *game, int index)
{
	int	y;

	y = 0;
	while (y < game->textures[index].img.height)
	{
		copy_texture_row(game, index, y);
		y++;
	}
}

static int	load_texture(t_game *game, int index)
{
	game->textures[index].img.img = mlx_xpm_file_to_image(game->mlx,
			game->textures[index].path, &game->textures[index].img.width,
			&game->textures[index].img.height);
	if (!game->textures[index].img.img)
	{
		print_error("Failed to load texture");
		return (-1);
	}
	printf("Loaded texture %d: %s, size: %dx%d\n",
		index, game->textures[index].path,
		game->textures[index].img.width,
		game->textures[index].img.height);
	game->textures[index].img.addr = mlx_get_data_addr(
			game->textures[index].img.img,
			&game->textures[index].img.bits_per_pixel,
			&game->textures[index].img.line_length,
			&game->textures[index].img.endian);
	copy_texture_to_buffer(game, index);
	return (0);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_texture(game, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
