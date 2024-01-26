/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakary <yakary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:37:33 by yakary            #+#    #+#             */
/*   Updated: 2023/03/14 15:11:47 by yakary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	x;

	if (!s)
		return (NULL);
	x = c;
	len = ft_strlen(s);
	s += len;
	if (x == '\0' && *s == '\0')
		return ((char *)s);
	while (len >= 0)
	{
		if (*s == x)
			return ((char *)s);
		s--;
		len--;
	}
	return (NULL);
}
