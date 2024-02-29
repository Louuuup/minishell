#include "minishell.h"

int	ft_pipe(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (DEBUG_ON)
		printf("(ft_pipe) ft_pipe called\n");
	if (cmd->next == NULL)
		return (NO_ERROR);
	if (pipe(pipe_fd) == -1)
		return (error_str("pipe error\n"));
	cmd->fd_out = pipe_fd[1];
	cmd->next->fd_in = pipe_fd[0];

	return (NO_ERROR);
}

int	ft_dup2(t_cmd *cmd)
{
	if (DEBUG_ON)
	{
		printf("(ft_dup2) ft_dup2 called\n");
		printf("(ft_dup2) cmd->fd_in: %d\n", cmd->fd_in);
		printf("(ft_dup2) cmd->fd_out: %d\n", cmd->fd_out);
	}
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	return (NO_ERROR);
}

int	fd_redirect(int fd, char *file, int redir_flag) 
{
	if (fd > 2)
		close(fd);
	if (redir_flag == REDIR_INPUT)
	{
		fd = open(file, O_RDONLY);
		if (access(file, R_OK) == -1)
		{
			error_str_file("permission denied: ", file);
			return (0);
		}
	}
	else if (redir_flag == REDIR_OVERWRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((access(file, W_OK)) == -1)
		{
			error_str_file("permission denied: ", file);
			return (0);
		}
	}
	else if (redir_flag == REDIR_APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((access(file, W_OK)) == -1)
		{	
			error_str_file("permission denied: ", file);
			return (0);
		}
	}
//	else if (redir_flag == REDIR_HEREDOC)
	else
		return (error_str("redir_flag error\n"));
	/*if (fd == -1)
		return (shell_error());*/
	return (fd);
}

static char *cmd_access(char *cmd, char **paths)
{
	int i;
	char *tmp;
	char *full_path;

	i = 0;
	if(*cmd == '\0')					//check if empty str as cmd in case of '' or ""
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)  //X_OK to check if executable
	{
		if (DEBUG_ON)
			printf("(cmd_access) found %s\n", cmd);
		return (gc_strdup(cmd));
	}
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)			//maybe need X_OK too ?
		{
			if (DEBUG_ON)
				printf("(cmd_access) found %s\n", tmp);
			full_path = gc_strdup(tmp);
			tmp = free_null(tmp);
			return (full_path);
		}
		tmp = free_null(tmp);
		i++;
	}
	return (NULL);
}

int command_valid(t_cmd *cmdt, char *cmd)
{
	char	*cmd_path;
	char	**paths;
	int i;

	i = 0;
	cmd_path = get_var(get_data()->env, "PATH");
	if (!cmd_path)
		return (FALSE);
	paths = ft_split(cmd_path, ':');
	if (!paths)
		return (FALSE);
	cmd_path = paths[0];
	paths[0] = ft_strtrim(paths[0], "PATHS=");
	cmd_path = free_null(cmd_path);
	while (paths[i])
	{
		paths[i] = charjoinfree(paths[i], '/');
		i++;
	}
	cmdt->path = cmd_access(cmd, paths);
		paths = arr_free((void **)paths);
	if (!cmdt->path)
		return (FALSE);
	return (TRUE);
}
