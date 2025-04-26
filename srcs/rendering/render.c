/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:28:35 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		if (y < WIN_HEIGHT / 2)
		{
			while (x < WIN_WIDTH)
			{
				my_mlx_pixel_put(&game->img, x, y, game->ceiling.value);
				x++;
			}
		}
		else
		{
			while (x < WIN_WIDTH)
			{
				my_mlx_pixel_put(&game->img, x, y, game->floor.value);
				x++;
			}
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	draw_floor_ceiling(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
