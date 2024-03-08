/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:30 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:30 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtincheck(t_cmd *cmd)
{
	if ((!ft_strncmp(cmd->cmd[0], "echo", 5)) || \
	(!ft_strncmp(cmd->cmd[0], "cd", 3)) || \
	(!ft_strncmp(cmd->cmd[0], "pwd", 4)) || \
	(!ft_strncmp(cmd->cmd[0], "export", 7)) || \
	(!ft_strncmp(cmd->cmd[0], "unset", 6)) || \
	(!ft_strncmp(cmd->cmd[0], "env", 4)) || \
	(!ft_strncmp(cmd->cmd[0], "exit", 5)))
		cmd->built_in = true;
	else
		cmd->built_in = false;
}


int	ft_idheredoc(t_idtok *id)
{
	if (id->app || id->out || id->here || id->in)
	{
		error_str("consecutive redirection\n");
		return (0);
	}
	id->here = true;
	return (1);
}

int	ft_idinput(t_idtok *id)
{
	if (id->app || id->out || id->here || id->in)
	{
		error_str("consecutive redirection\n");
		return (0);
	}
	id->in = true;
	return (1);
}

int	ft_idappend(t_idtok *id)
{
	if (id->app || id->out || id->here || id->in)
	{
		error_str("consecutive redirection\n");
		return (0);
	}
	id->app = true;
	return (1);
}

int	ft_idoutput(t_idtok *id)
{
	if (id->app || id->out || id->here || id->in)
	{
		error_str("consecutive redirection\n");
		return (0);
	}
	id->out = true;
	return (1);
}
