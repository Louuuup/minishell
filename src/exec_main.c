/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:13:19 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/11 14:55:59 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_pid(t_data *data)
{
	int		status;
	t_cmd	*cmd;

	if (DEBUG_ON)
		printf("(wait_pid) wait_pid called\n");
	cmd = data->cmd;
	while (cmd != NULL)
	{
		waitpid(cmd->pid, &status, 0);
		if (!cmd->next)
		{
			if (data->code_exit != 127)
			{
				if (!cmd->cmd)
					exit_code(0);
				else if (WIFEXITED(status))
					exit_code((WEXITSTATUS(status)));
				else if (WIFSIGNALED(status))
					exit_code(128 +(WTERMSIG(status)));
			}
		}
		cmd = cmd->next;
	}
	return (1);
}

void	fork_exec(t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		error_str("fork error\n");
	if (cmd->pid == 0)
	{
		if (cmd->next != NULL)
			close(cmd->next->fd_in);
		fork_exec_extra(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (cmd->fd_in != STDIN_FILENO)
		{
			if (close(cmd->fd_in) == -1)
				shell_error();
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			if (close(cmd->fd_out) == -1)
				shell_error();
		}
	}
}

void	exec_cmd(t_cmd *cmdt)
{
	if (DEBUG_ON)
		printf("(exec_cmd) exec_cmd called\n");
	if (cmdt->cmd)
	{
		if (cmdt->cmd[0][0] == 0)
		{
			get_data()->code_exit = 0;
			return ;
		}
		if (command_valid(cmdt, cmdt->cmd[0]) == TRUE && cmdt->path != NULL)
		{
			fork_exec(cmdt);
		}
		else
		{
			get_data()->code_exit = 127;
			if (!ft_strcmp(cmdt->cmd[0], "\"\"") || \
				!ft_strcmp(cmdt->cmd[0], "\'\'"))
				error_str(gc_strjoin("", "command not found\n"));
			else
				error_str(gc_strjoin(cmdt->cmd[0], ": command not found\n"));
		}
	}
}

int	exec_builtin(t_cmd *cmd)
{
	if (get_data()->cmd->next)
		cmd->pid = fork();
	if (cmd->pid == 0 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->next)
		close(cmd->next->fd_in);
	if (cmd->pid == 0 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_out);
	if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "echo", 5))
		get_data()->code_exit = b_echo(cmd);
	if (cmd->pid == 0 && !ft_strncmp (cmd->cmd[0], "cd", 3))
		get_data()->code_exit = b_cd(cmd);
	else if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "pwd", 4))
		get_data()->code_exit = b_pwd(cmd);
	else if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "export", 7))
		get_data()->code_exit = b_export(get_data(), cmd);
	else if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "unset", 6))
		get_data()->code_exit = b_unset(cmd);
	else if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "env", 4))
		get_data()->code_exit = b_env(cmd);
	else if (cmd->pid == 0 && !ft_strncmp(cmd->cmd[0], "exit", 5))
		get_data()->code_exit = b_exit(cmd, cmd->fd_out);
	if (cmd->pid == 0 && get_data()->cmd->next)
		builtin_exit(cmd);
	return (get_data()->code_exit);
}

void	exec_main(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (ft_pipe(cmd))
			return ;
		if (redirect_check(cmd))
			return ;
		if (cmd->built_in)
			exec_builtin(cmd);
		else
			exec_cmd(cmd);
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}
