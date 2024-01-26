/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoinfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:15:05 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/08 14:21:29 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*charjoinfree(char *str, char c)
{
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = ft_calloc((len + 2), sizeof(char));
	ft_strlcpy(new, str, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}
