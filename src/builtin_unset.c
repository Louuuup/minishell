/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/09 00:55:06 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_cmd *cmdt)
{
	int		i;
	char	*var;
	t_data	*data;

	data = get_data();
	i = 1;
	while (cmdt->cmd[i])
	{
		if (export_valid(cmdt->cmd[i]) == FALSE)
		{
			return (error_str_file("Unset: not a valid identifier :", cmdt->cmd[i]));
		}
		var = get_var(data->env, cmdt->cmd[i]);
		if (var)
			data->env = rm_var(data, cmdt->cmd[i]);
		i++;
	}
	return (NO_ERROR);
}
