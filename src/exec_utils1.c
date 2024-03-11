/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:35:16 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/11 14:55:28 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_exec_extra(t_cmd *cmd)
{
	signal(SIGQUIT, sigchildquit);
	signal(SIGINT, sigchildint);
	ft_dup2(cmd);
	execve(cmd->path, cmd->cmd, get_data()->env);
}

void	builtin_exit(t_cmd *cmd)
{
	if (cmd->fd_out != STDOUT_FILENO)
		close (cmd->fd_out);
	exit(get_data()->code_exit);
}
