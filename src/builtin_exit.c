/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:55 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/07 12:31:06 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_valid_err(int code)
{
	t_data	*data;

	data = get_data();
	if (code > 255)
		data->code_exit = code % 256;
	else if (code < 0)
		data->code_exit = 256 + code;
	else
		data->code_exit = code;
}

void	exit_code(int code)
{
	t_data	*data;

	data = get_data();
	if (DEBUG_ON)
		printf("(exit_code) new code: %d\n", code);
	data->code_exit = code;
	data = get_data();
	if (DEBUG_ON)
		printf("(exit_code) new code: %d\n", code);
	data->code_exit = code;
}

void	b_exit(t_cmd *cmd)
{
	char	*tmp;

	if (cmd)
	{
		if (cmd->index != 0)
			return ;
		if (cmd->cmd[1] && cmd->cmd[2])
			get_data()->code_exit = 1;
		else if (cmd->cmd[1])
		{
			if (ft_isnumber(cmd->cmd[1]))
				get_data()->code_exit = ft_atoi(cmd->cmd[1]);
			else
			{
				tmp = gc_strjoin("exit: ", cmd->cmd[1]);
				error_str_code(tmp, ": numeric argument required\n", 255);
				gc_free_one(get_data()->memblock, tmp);
			}
		}
	}
	get_valid_err(get_data()->code_exit);
	if (!write(1, "exit\n", 5))
		return ;
	gc_free_all(get_data()->memblock);
	exit(get_data()->code_exit);
}
