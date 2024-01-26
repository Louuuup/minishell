/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxkramer <maxkramer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:23:33 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/01/13 16:17:13 by maxkramer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		*ptr = NULL;
		free(ptr);
	}
}

void	*free_null(void *ptr)
{
	if (ptr)
		free(ptr);

	return (NULL);
}

void	*arr_free(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i] != NULL)
	{
		arr[i] = free_null(arr[i]);
		i++;
	}
	free_null(arr);
	return (NULL);
}
