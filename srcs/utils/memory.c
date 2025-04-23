/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:32:54 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 2차원 그리드(맵) 메모리 할당
 */
char	**allocate_grid(int height, int width)
{
	char	**grid;
	int		i;
	int		j;

	// 행 메모리 할당
	grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	
	// 각 행에 대한 열 메모리 할당
	i = 0;
	while (i < height)
	{
		grid[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!grid[i])
		{
			// 할당 실패 시 이전에 할당한 메모리 해제
			j = 0;
			while (j < i)
				free(grid[j++]);
			free(grid);
			return (NULL);
		}
		// 초기값으로 공백 설정
		j = 0;
		while (j < width)
			grid[i][j++] = ' ';
		grid[i][j] = '\0';
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

/**
 * 메모리를 특정 값으로 초기화
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

/**
 * 메모리 할당 및 0으로 초기화
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	// 오버플로우 체크
	if (count > 0 && size > 0 && count > SIZE_MAX / size)
		return (NULL);
	
	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	
	// 할당된 메모리를 0으로 초기화
	ft_memset(ptr, 0, total_size);
	return (ptr);
}