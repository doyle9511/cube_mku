/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:57:54 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 17:03:19 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"

static char	*extract_path(char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (NULL);
	path = ft_strdup(line + i);
	if (!path)
		return (NULL);
	i = ft_strlen(path) - 1;
	while (i >= 0 && path[i] == ' ')
		path[i--] = '\0';
	return (path);
}

int	parse_texture_line(t_game *game, char *line)
{
	char	*path;

	path = extract_path(line);
	printf("Parsing texture: %s, Path: %s\n", line, path);
	if (!path)
	{
		print_error("Invalid texture path");
		return (-1);
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->textures[0].path = path;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->textures[1].path = path;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->textures[2].path = path;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->textures[3].path = path;
	else
	{
		free(path);
		print_error("Invalid texture identifier");
		return (-1);
	}
	return (0);
}
