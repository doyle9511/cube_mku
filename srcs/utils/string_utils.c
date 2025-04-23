/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/09 17:49:08 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * 문자열 길이 계산
 */
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * 두 문자열을 n바이트만큼 비교
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * 문자열 복제
 */
char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		len;
	int		i;

	len = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/**
 * 문자열에서 특정 부분을 추출
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/**
 * 문자 세기 (ft_split 보조 함수)
 */
static int	count_chars(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

/**
 * 단어 추출 (ft_split 보조 함수)
 */
static char	*extract_word(const char *s, char c, int *i)
{
	char	*word;
	int		word_len;
	int		j;

	word_len = 0;
	while (s[*i + word_len] && s[*i + word_len] != c)
		word_len++;
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < word_len)
	{
		word[j] = s[*i + j];
		j++;
	}
	word[j] = '\0';
	*i += word_len;
	return (word);
}

/**
 * 문자열 분할 (구분자에 따라 분리)
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	word_count = count_chars(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		result[j] = extract_word(s, c, &i);
		if (!result[j])
			return (NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}
