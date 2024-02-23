#include "minishell.h"

void fork_exec(t_cmd *cmd)
{
	int		pid;

	pid = 0;
	pid = fork();
	if (pid == -1)
		error_str("fork error\n");
	if (pid == 0)
	{
		execve(cmd->cmd[0], cmd->cmd, get_data()->env);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	exec_cmd(t_cmd *cmdt)
{
	if (DEBUG_ON)
		printf("(exec_cmd) exec_cmd called\n");
	if (cmdt->cmd)
	{
		if (command_valid(cmdt, cmdt->cmd[0]) == TRUE)
		{
			fork_exec(cmdt);
		}
		else
		{	
			error_str(gc_strjoin(cmdt->cmd[0], ": command not found\n"));
			// error_str("command not found\n");
		}
	}
}

void redirect_check(t_cmd *cmd)
{
	if (cmd->infile && cmd->in_flag == REDIR_INPUT)
		cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, cmd->in_flag);
	if (cmd->outfile && cmd->out_flag == REDIR_OVERWRITE)
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
	if (cmd->outfile && cmd->out_flag == REDIR_APPEND)
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
}

void	exec_builtin(t_cmd *cmd)
{
	if (DEBUG_ON)
		printf("(exec_builtin) exec_builtin called\n");
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		b_echo(cmd);
	if (!ft_strncmp (cmd->cmd[0], "cd", 3))
		b_cd(cmd);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		b_pwd(cmd);
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		b_export(cmd);
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		b_unset(cmd);
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		b_env(cmd);
	// else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
	// 	b_exit(cmd);
}

void	exec_main(t_data *data)
{
	t_cmd	*cmd;

	if (DEBUG_ON)
		printf("(exec_main) exec_main called\n");
	cmd = data->cmd;
	if (!cmd)
		return ;
	while (cmd->next)
	{
		if (ft_pipe(cmd))
			return ;
		cmd = cmd->next;
	}
	cmd = data->cmd;
	// cmd_status(cmd); // debug
	while (cmd)
	{
		redirect_check(cmd);
		if (ft_dup2(cmd))
			return ;
		if (cmd->built_in)
			exec_builtin(cmd);
		else
			exec_cmd(cmd);
		cmd = cmd->next;
	}
}
