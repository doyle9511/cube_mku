/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:35:23 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:04:14 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//parse_map.c
int		parse_map(t_game *game, char *file_path);
//parse_map2.c
int		parse_line(t_game *game, char *line);
void	free_string_array(char **array);
int		find_map_dimensions(char **lines, t_game *game, int *start_line);
int		copy_map_data(char **lines, t_game *game, int start_line);
int		read_map_file_part1(char *file_path, int *fd, char *buffer);
//parse_colors.c
int		parse_color_line(t_game *game, char *line);
//parse_colors2.c
int		create_rgb(t_color *color);
int		ft_atoi(const char *str);
int		free_values_and_return_error(char **values);
//parse_textures.c
int		load_textures(t_game *game);
//parse_textures2.c
int		parse_texture_line(t_game *game, char *line);
/* parser/validate_map.c */
int		validate_map(t_game *game);
int		check_walls(t_map *map);
int		check_player(t_map *map);
//validate2_map.c
int		check_walls(t_map *map);
#endif 