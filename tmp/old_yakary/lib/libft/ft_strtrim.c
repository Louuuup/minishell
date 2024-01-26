/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakary <yakary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:44:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/03/14 15:11:28 by yakary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	right_strip(const char *str, const char *set);
static size_t	left_strip(const char *str, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	char	*output;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	first = left_strip(s1, set);
	last = right_strip(s1, set);
	if (first >= last)
		return (ft_strdup(""));
	output = ft_calloc(sizeof(char), 1 + last - first);
	if (!output)
		return (NULL);
	ft_strlcpy(output, s1 + first, 1 + last - first);
	return (output);
}

static size_t	left_strip(const char *str, const char *set)
{
	size_t	set_len;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	set_len = ft_strlen(set);
	i = 0;
	while (i < str_len)
	{
		if (!ft_memchr(set, str[i], set_len))
			break ;
		i++;
	}
	return (i);
}

static size_t	right_strip(const char *str, const char *set)
{
	size_t	set_len;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(str);
	set_len = ft_strlen(set);
	i = 0;
	while (i < str_len)
	{
		if (!ft_memchr(set, str[str_len - i - 1], set_len))
			break ;
		i++;
	}
	return (str_len - i);
}
