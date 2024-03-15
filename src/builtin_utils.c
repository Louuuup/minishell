/* ************************************************************************** */
/*																			*/
/*			                                            :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:52 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 13:15:40 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (error_str_code("invalid identifier :", (str), 1));
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (error_str_code("invalid identifier :", (str), 1));
		i++;
	}
	return (NO_ERROR);
}

char	*var_name(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_str = ft_substr(str, 0, i);
	if (DEBUG_ON)
		printf("(var_name) found %s in %s\n", new_str, str);
	return (new_str);
}

char	*var_value(char *str)
{
	int		i;
	char	*new_str;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = ft_strdup(str + i + 1);
	new_str = ft_strtrim(tmp, " ");
	tmp = free_null(tmp);
	if (DEBUG_ON)
		printf("(var_value) found %s in %s\n", new_str, str);
	return (new_str);
}
