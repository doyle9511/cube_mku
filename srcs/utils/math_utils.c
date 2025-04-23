/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 16:33:10 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 각도를 라디안으로 변환
 */
double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

/**
 * 최대값 반환
 */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * 최소값 반환
 */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * 부동소수점 숫자의 정수부 추출
 */
int	ft_floor(double x)
{
	return ((int)x);
}

/**
 * 부동소수점 숫자의 소수부 추출
 */
double	ft_fract(double x)
{
	return (x - ft_floor(x));
}