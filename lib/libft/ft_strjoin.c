/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:33:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/05 15:26:31 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_a;
	char	*str_b;
	size_t	size;
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	size = s1_size + s2_size + 1;
	if (!s1 || !s2)
		return (0);
	if (size <= 0)
		return (0);
	str_a = malloc(size * sizeof(char));
	if (!str_a)
		return (NULL);
	str_b = str_a + s1_size;
	ft_memcpy(str_a, s1, s1_size);
	ft_memcpy(str_b, s2, s2_size);
	str_a[size - 1] = '\0';
	return (str_a);
}
