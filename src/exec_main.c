#include "minishell.h"

void close_fds_alt(t_cmd *cmd, int fd_in, int fd_out)
{
	t_cmd *tmp;

	if (DEBUG_ON)
		printf("(close_fds) close_fds called\n");
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->fd_in != fd_in && cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != fd_out && cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = tmp;
	}
}

void fork_exec(t_cmd *cmd)
{
    pid_t pid;

	pid = fork();
	if (pid < 0)
		error_str("fork error\n");
    if (pid == 0)
	{
		signal(SIGQUIT, sigchildquit);
		signal(SIGINT, sigchildint);
		ft_dup2(cmd);
		execve(cmd->path, cmd->cmd, NULL);
        exit(EXIT_FAILURE);
    }
	else
	{
		signal(SIGINT, SIG_IGN);
		if (DEBUG_ON)
			printf("(fork_exec) parent process\n");
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
		if (command_valid(cmdt, cmdt->cmd[0]) == TRUE && cmdt->path != NULL)
		{
			fork_exec(cmdt);
		}
		else
		{	
			get_data()->code_exit = 127;			
			error_str(gc_strjoin(cmdt->cmd[0], ": command not found\n"));
		}
	}
}


void	exec_builtin(t_cmd *cmd)
{
	if (DEBUG_ON)
	{	
		printf("(exec_builtin) exec_builtin called\n");
		printf("(exec_builtin) cmd->cmd[0]: %s\n", cmd->cmd[0]);
		printf("(exec_builtin) fd_in: %d\n", cmd->fd_in);
		printf("(exec_builtin) fd_out: %d\n", cmd->fd_out);
	}
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
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		b_exit(cmd);
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
		if (DEBUG_ON)
			cmd_status(cmd);
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
