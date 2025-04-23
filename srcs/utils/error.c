/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 17:58:50 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 문자열을 지정된 파일 디스크립터에 출력
 */
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/**
 * 오류 메시지 출력 후 프로그램 종료
 */
void	error_exit(char *message)
{
	// 표준 오류 출력으로 메시지 출력
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	
	// 프로그램 종료
	exit(1);
}

/**
 * 오류 메시지 출력 (종료는 하지 않음)
 */
void	print_error(char *message)
{
	// 표준 오류 출력으로 메시지 출력
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
