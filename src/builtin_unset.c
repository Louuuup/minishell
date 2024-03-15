/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/15 16:26:35 by fboivin          ###   ########.fr       */
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
		if (export_valid(cmdt->cmd[i]) == ERROR)
			data->code_exit = 1;
		else if (get_var(data->env, cmdt->cmd[i]) == NULL)
			error_str_code("Unset: identifier not in environnement : ", \
			cmdt->cmd[i], 1);
		else
		{
			var = get_var(data->env, cmdt->cmd[i]);
			if (var)
				data->env = rm_var(data, cmdt->cmd[i], NULL);
		}
		i++;
	}
	return (data->code_exit);
}
