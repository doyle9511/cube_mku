/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mku <mku@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:49:49 by mku               #+#    #+#             */
/*   Updated: 2025/04/26 16:47:48 by mku              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"

int	free_values_and_return_error(char **values)
{
	int	i;

	if (values)
	{
		i = 0;
		while (values[i])
			free(values[i++]);
		free(values);
	}
	return (-1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	validate_color_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_error("Color values must be between 0 and 255");
		return (-1);
	}
	return (0);
}

int	create_rgb(t_color *color)
{
	if (validate_color_values(color->r, color->g, color->b) == -1)
		return (-1);
	color->value = (color->r << 16) | (color->g << 8) | color->b;
	return (0);
}
