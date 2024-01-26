/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakary <yakary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:01:32 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/03/14 15:16:55 by yakary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	if (!dst || !src)
		return (dst);
	i = 0;
	x = (unsigned char *)dst;
	y = (unsigned char *)src;
	while (i < n)
	{
		*x++ = *y++;
		i++;
	}
	return (dst);
}
