/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:59:02 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:59:03 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(const char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	count_words(const char *str, char charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_charset(*str, charset) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_charset(*str, charset))
			in_word = 0;
		str++;
	}
	return (count);
}

static int	len_word(char const *str, char charset)
{
	int	len;

	len = 0;
	while (*str && !is_charset(*str, charset))
	{
		len++;
		str++;
	}
	return (len);
}

static char	**freemem(char **result, int i)
{
	while (--i >= 0)
		free(result[i]);
	free(result);
	return (NULL);
}

char	**ft_split_fd(char const *s, char c)
{
	int		i;
	int		j;
	char	**result;
	int		word_count;

	i = -1;
	j = 0;
	word_count = count_words(s, c);
	result = (char **)ft_calloc(sizeof(char *), (size_t)(word_count + 1));
	if (!result)
		return (NULL);
	while (++i < word_count)
	{
		while (is_charset(*s, c))
			s++;
		result[i] = (char *)malloc(sizeof(char) * (len_word(s, c) + 1));
		if (!result[i])
			return (freemem(result, i));
		while (*s && !is_charset(*s, c))
			result[i][j++] = *s++;
		result[i][j] = '\0';
		j = 0;
	}
	result[i] = 0;
	return (result);
}
