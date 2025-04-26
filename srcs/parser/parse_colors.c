/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/26 16:47:35 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

static int	parse_color_string(t_color *color, char *str)
{
	char	**values;
	int		count;

	values = ft_split(str, ',');
	if (!values)
		return (-1);
	count = 0;
	while (values[count])
		count++;
	if (count != 3)
	{
		print_error("Color format must be R,G,B");
		return (free_values_and_return_error(values));
	}
	color->r = ft_atoi(values[0]);
	color->g = ft_atoi(values[1]);
	color->b = ft_atoi(values[2]);
	count = 0;
	while (values[count])
		free(values[count++]);
	free(values);
	if (create_rgb(color) == -1)
		return (-1);
	return (0);
}

static char	*extract_color_data(char *line)
{
	int		i;
	char	*color_data;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (NULL);
	color_data = ft_strdup(line + i);
	if (!color_data)
		return (NULL);
	return (color_data);
}

int	parse_color_line(t_game *game, char *line)
{
	char	*color_data;
	int		result;

	color_data = extract_color_data(line);
	if (!color_data)
	{
		print_error("Invalid color data");
		return (-1);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
		result = parse_color_string(&game->floor, color_data);
	else if (ft_strncmp(line, "C ", 2) == 0)
		result = parse_color_string(&game->ceiling, color_data);
	else
	{
		free(color_data);
		print_error("Invalid color identifier");
		return (-1);
	}
	free(color_data);
	return (result);
}
