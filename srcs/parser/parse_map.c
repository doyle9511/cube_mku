/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/23 07:09:41 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 파일 확장자 검증
 */
int	validate_file_extension(char *file_path)
{
	char	*ext;

	ext = file_path + ft_strlen(file_path) - 4;
	if (ft_strlen(file_path) < 5 || ft_strncmp(ext, ".cub", 4) != 0)
	{
		print_error("Invalid file extension (should be .cub)");
		return (-1);
	}
	return (0);
}

/**
 * 한 줄 파싱 - 텍스처나 색상 정보인지 확인하고 처리
 */
static int	parse_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_line(game, line));
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(game, line));
	return (0);
}

/**
 * 맵 파일 읽고 파싱 (part 1)
 */
static int	read_map_file_part1(char *file_path, int *fd, char *buffer)
{
	int	bytes_read;

	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
	{
		print_error("Failed to open map file");
		return (-1);
	}
	bytes_read = read(*fd, buffer, 4095);
	if (bytes_read <= 0)
	{
		print_error("Failed to read map file or file is empty");
		close(*fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	return (0);
}

/**
 * 맵 파일 읽고 파싱
 */
int read_map_file(t_game *game, char *file_path)
{
    int     fd;
    char    buffer[4096];
    char    **lines;
    int     i;
    int     result;

    if (read_map_file_part1(file_path, &fd, buffer) == -1)
        return (-1);
    
    lines = ft_split(buffer, '\n');
    if (!lines)
        return (-1);
    
    i = 0;
    result = 0;
    while (lines[i] && result == 0)
    {
        result = parse_line(game, lines[i]);
        i++;
    }
    
    // 메모리 해제
    i = 0;
    while (lines[i])
        free(lines[i++]);
    free(lines);
    
    return (result);
}

/**
 * 맵 데이터 추출 - 맵 높이와 시작 라인 찾기
 */
static int	find_map_dimensions(char **lines, t_game *game, int *start_line)
{
	int	i;

	// 텍스처와 색상 정보 건너뛰기
	i = 0;
	while (lines[i] && (ft_strncmp(lines[i], "NO ", 3) == 0
		|| ft_strncmp(lines[i], "SO ", 3) == 0
		|| ft_strncmp(lines[i], "WE ", 3) == 0
		|| ft_strncmp(lines[i], "EA ", 3) == 0
		|| ft_strncmp(lines[i], "F ", 2) == 0
		|| ft_strncmp(lines[i], "C ", 2) == 0
		|| lines[i][0] == '\0'))
		i++;
	
	*start_line = i;
	
	// 맵 높이 계산
	game->map.height = 0;
	while (lines[i])
	{
		game->map.height++;
		i++;
	}
	
	// 맵 너비 계산 (가장 긴 줄 기준)
	game->map.width = 0;
	i = *start_line;
	while (i < *start_line + game->map.height)
	{
		if (ft_strlen(lines[i]) > game->map.width)
			game->map.width = ft_strlen(lines[i]);
		i++;
	}
	return (0);
}

/**
 * 맵 데이터 복사
 */
static int	copy_map_data(char **lines, t_game *game, int start_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(lines[start_line + i]))
		{
			game->map.grid[i][j] = lines[start_line + i][j];
			j++;
		}
		// 남은 부분은 공백으로 채우기
		while (j < game->map.width)
		{
			game->map.grid[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * 메모리 해제 유틸리티 함수
 */
static void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

/**
 * 맵 데이터 추출 (텍스처와 색상 정보 이후의 라인들)
 */
static int	extract_map_data(t_game *game, char *file_content)
{
	char	**lines;
	int		start_line;

	lines = ft_split(file_content, '\n');
	if (!lines)
		return (-1);
	
	find_map_dimensions(lines, game, &start_line);
	
	// 맵 그리드 할당
	game->map.grid = allocate_grid(game->map.height, game->map.width);
	if (!game->map.grid)
	{
		free_string_array(lines);
		return (-1);
	}
	
	// 맵 데이터 복사
	copy_map_data(lines, game, start_line);
	
	// 메모리 해제
	free_string_array(lines);
	return (0);
}

/**
 * 맵 파싱 메인 함수 - part 1
 */
static int	parse_map_part1(char *file_path, int *fd, char *buffer)
{
	int	bytes_read;

	if (validate_file_extension(file_path) == -1)
		return (-1);
	
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
	{
		print_error("Failed to open map file");
		return (-1);
	}
	
	bytes_read = read(*fd, buffer, 9999);
	if (bytes_read <= 0)
	{
		print_error("Failed to read map file or file is empty");
		close(*fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	close(*fd);
	return (0);
}

/**
 * 맵 파싱 메인 함수
 */
int	parse_map(t_game *game, char *file_path)
{
	char	buffer[10000];
	int		fd;

	if (parse_map_part1(file_path, &fd, buffer) == -1)
		return (-1);
	
	// 텍스처와 색상 정보 파싱
	if (read_map_file(game, file_path) == -1)
		return (-1);
	
	// 맵 데이터 추출
	if (extract_map_data(game, buffer) == -1)
	{
		print_error("Failed to extract map data");
		return (-1);
	}
	
	// 맵 유효성 검사
	if (validate_map(game) == -1)
	{
		print_error("Invalid map");
		return (-1);
	}
	
	return (0);
}