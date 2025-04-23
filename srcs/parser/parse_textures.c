/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/17 21:03:18 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 텍스처 경로 추출
 */
static char	*extract_path(char *line)
{
	int		i;
	char	*path;

	// 텍스처 식별자 건너뛰기 ("NO ", "SO ", "WE ", "EA ")
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	
	// 공백 건너뛰기
	while (line[i] && line[i] == ' ')
		i++;
	
	// 경로가 없으면 에러
	if (!line[i])
		return (NULL);
	
	// 경로 복제
	path = ft_strdup(line + i);
	if (!path)
		return (NULL);
	
	// 경로에서 후행 공백 제거
	i = ft_strlen(path) - 1;
	while (i >= 0 && path[i] == ' ')
		path[i--] = '\0';
	
	return (path);
}

/**
 * 텍스처 식별자 라인 파싱 (NO, SO, WE, EA)
 */
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
	
	// 텍스처 종류에 따라 저장
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

/**
 * 텍스처 데이터를 버퍼에 복사 (행 처리)
 */
static void	copy_texture_row(t_game *game, int index, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < game->textures[index].img.width)
	{
		// 텍스처 이미지에서 픽셀 색상 추출
		color = *(unsigned int *)(game->textures[index].img.addr
				+ (y * game->textures[index].img.line_length
					+ x * (game->textures[index].img.bits_per_pixel / 8)));
		
		// 텍스처 버퍼에 색상 저장
		game->tex_buf[index][y * TEX_WIDTH + x] = color;
		x++;
	}
}

/**
 * 텍스처 데이터를 버퍼에 복사
 */
void	copy_texture_to_buffer(t_game *game, int index)
{
	int	y;

	y = 0;
	while (y < game->textures[index].img.height)
	{
		copy_texture_row(game, index, y);
		y++;
	}
}

/**
 * XPM 파일에서 텍스처 로드
 */
static int	load_texture(t_game *game, int index)
{
	// mlx_xpm_file_to_image: XPM 파일을 이미지로 변환
	// 파일 경로, 너비와 높이를 저장할 포인터를 인자로 받음
	game->textures[index].img.img = mlx_xpm_file_to_image(game->mlx,
			game->textures[index].path, &game->textures[index].img.width,
			&game->textures[index].img.height);
	
	if (!game->textures[index].img.img)
	{
		print_error("Failed to load texture");
		return (-1);
	}

	    // 디버그 출력 추가
    printf("Loaded texture %d: %s, size: %dx%d\n", 
           index, game->textures[index].path, 
           game->textures[index].img.width, 
           game->textures[index].img.height);
	
	// mlx_get_data_addr: 이미지 데이터 주소 가져오기
	// 이미지 포인터, 픽셀 비트 수, 한 줄 길이, 엔디안을 저장할 포인터를 인자로 받음
	game->textures[index].img.addr = mlx_get_data_addr(
			game->textures[index].img.img,
			&game->textures[index].img.bits_per_pixel,
			&game->textures[index].img.line_length,
			&game->textures[index].img.endian);
	
	// 텍스처 버퍼에 복사
	copy_texture_to_buffer(game, index);
	
	return (0);
}

/**
 * 모든 텍스처 로드
 */
int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_texture(game, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}