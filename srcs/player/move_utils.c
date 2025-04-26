/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:17:09 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 16:06:17 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/move.h"
#include "../../includes/cub3d.h"

int	is_wall(t_map *map, double x, double y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	if (map->grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}
