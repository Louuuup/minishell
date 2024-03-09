/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:49 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 23:49:07 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_flag(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != '-')
		return (NO);
	if (str[i] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (YES);
	}
	return (NO);
}

int	b_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->cmd[i] && n_flag(cmd->cmd[i]) == YES)
	{
		i++;
		while (n_flag(cmd->cmd[i]) == YES)
			i++;
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], cmd->fd_out);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', cmd->fd_out);
		i++;
	}
	if (n_flag(cmd->cmd[1]) == NO)
		ft_putchar_fd('\n', cmd->fd_out);
	return (NO_ERROR);
}
