/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:12:18 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/rendering.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_game *game, int x, t_ray *ray)
{
	int	y;
	int	color;

	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			color = RED;
		else
			color = GREEN;
	}
	else
	{
		if (ray->step_y > 0)
			color = BLUE;
		else
			color = YELLOW;
	}
	if (ray->side == 1)
		color = color / 2;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}
