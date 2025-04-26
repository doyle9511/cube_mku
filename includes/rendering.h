/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:58 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:04:54 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

/* draw.c*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_game *game, int x, t_ray *ray);
/* render.c */
int		render_frame(t_game *game);
void	draw_floor_ceiling(t_game *game);

/* raycasting.c */
void	raycasting(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	calculate_wall_height(t_ray *ray);

/* textures.c */
void	calculate_wall_texture(t_game *game, t_ray *ray);
void	draw_wall_texture(t_game *game, t_ray *ray, int x);

//ray.c
void	init_ray(t_game *game, t_ray *ray, int x);
#endif