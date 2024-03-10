/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:35:16 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:06:16 by ycyr-roy         ###   ########.fr       */
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
