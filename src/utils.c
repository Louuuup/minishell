/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:35 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/15 12:19:41 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strdup(char *str)
{
	char	*new_str;

	if (str == NULL)
		return (NULL);
	new_str = gc_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_strlcpy(new_str, str, ft_strlen(str) + 1);
	return (new_str);
}

char	**gc_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (DEBUG_ON)
		printf("(gc_split) start\n");
	tab = gc_calloc(ft_strlen(str) + 1, sizeof(char *));
	while (str[i])
	{
		if (str[i] != c)
		{
			k = 0;
			tab[j] = gc_calloc(ft_strlen(str) + 1, sizeof(char));
			while (str[i] && str[i] != c)
				tab[j][k++] = str[i++];
			tab[j++][k] = '\0';
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
