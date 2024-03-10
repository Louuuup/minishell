/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 14:48:28 by ycyr-roy         ###   ########.fr       */
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
			return (error_str_code("Unset: not a valid identifier : ", \
			cmdt->cmd[i], 1));
		else if (get_var(data->env, cmdt->cmd[i]) == NULL)
			return (error_str_code("Unset: identifier not in environnement : ", \
			cmdt->cmd[i], 1));
		var = get_var(data->env, cmdt->cmd[i]);
		if (var)
			data->env = rm_var(data, cmdt->cmd[i]);
		i++;
	}
	return (NO_ERROR);
}
