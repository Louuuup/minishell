/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:59:30 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:49:16 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arr_dup(char **arr)
{
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = ft_calloc(arr_len(arr) + 1, sizeof(char *));
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	return (new_arr);
}
