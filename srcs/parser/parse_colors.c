/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/23 06:47:11 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 메모리 해제 및 에러 반환
 */
static int	free_values_and_return_error(char **values)
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

/**
 * 문자열을 정수로 변환
 */
static int	ft_atoi(const char *str)
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

/**
 * RGB 색상 값 검증
 */
static int	validate_color_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_error("Color values must be between 0 and 255");
		return (-1);
	}
	return (0);
}

/**
 * RGB 값을 하나의 정수로 변환
 */
int	create_rgb(t_color *color)
{
	if (validate_color_values(color->r, color->g, color->b) == -1)
		return (-1);
	
	// RGB 값을 하나의 32비트 정수로 변환 (0xRRGGBB 형식)
	color->value = (color->r << 16) | (color->g << 8) | color->b;
	return (0);
}

/**
 * 색상 문자열 파싱
 */
static int	 parse_color_string(t_color *color, char *str)
{
	char	**values;
	int		count;

	// 쉼표로 분리
	values = ft_split(str, ',');
	if (!values)
		return (-1);
	
	// RGB 값 3개 확인
	count = 0;
	while (values[count])
		count++;
	
	if (count != 3)
	{
		print_error("Color format must be R,G,B");
		return (free_values_and_return_error(values));
	}
	
	// RGB 값 변환
	color->r = ft_atoi(values[0]);
	color->g = ft_atoi(values[1]);
	color->b = ft_atoi(values[2]);
	
	// 메모리 해제
	count = 0;
	while (values[count])
		free(values[count++]);
	free(values);
	
	// RGB 값 검증 및 변환
	if (create_rgb(color) == -1)
		return (-1);
	
	return (0);
}

/**
 * 색상 데이터 추출
 */
static char	*extract_color_data(char *line)
{
	int		i;
	char	*color_data;

	// 색상 식별자 건너뛰기 ("F ", "C ")
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	
	// 공백 건너뛰기
	while (line[i] && line[i] == ' ')
		i++;
	
	// 색상 데이터가 없으면 에러
	if (!line[i])
		return (NULL);
	
	// 색상 데이터 복제
	color_data = ft_strdup(line + i);
	if (!color_data)
		return (NULL);
	
	return (color_data);
}

/**
 * 색상 식별자 라인 파싱 (F, C)
 */
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
	
	// 색상 종류에 따라 파싱
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