/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:42:00 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:05:08 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

typedef struct s_map	t_map;
/* utils/error.c */
void	error_exit(char *message);
void	print_error(char *message);

/* utils/memory.c */
void	free_map(t_map *map);
char	**allocate_grid(int height, int width, int i, int j);

/* utils/math_utils.c */
double	deg_to_rad(double angle);
//int		is_wall(t_map *map, int x, int y);

/* utils/string_utils.c */
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//split.c
char	**ft_split(char const *s, char c);

#endif