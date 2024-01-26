#include "minishell.h"

void	ft_dup2(int fd, int std)
{
	int	err;

	err = dup2(fd, std);
	if (err == -1)
		ft_error(ERR_DUP);
	close(fd);
}

void	ft_pipe(t_cmd *cmd)
{
	int	pipefd[2];
	int	err;

	err = pipe(pipefd);
	if (err == -1)
		ft_error(ERR_PIPE);
	cmd->fd[0] = pipefd[0];
	cmd->next->fd[1] = pipefd[1];
}
char *ft_get_env(char *str, char **env)
{
	int		i[2];
	int		j;
	char	*out;

	j = 0;
	i[0] = 0;
	//tmp

	//tmp
	while (env[i[0]] && !(ft_strnstr(env[i[0]], str, ft_strlen(str)) && find_symbol('=', env[i[0]])))
		i[0]++;
	if (!env[i[0]])
		return (NULL);
	out = ft_calloc(ft_strlen(env[i[0]]) - ft_strlen(str) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i[1] = ft_strlen(str) + 1;
	while (env[i[0]][i[1]])
	{
		out[j] = env[i[0]][i[1]];
		i[1]++;
		j++;
	}
	return (out);

}

char	*cmd_fullpath(t_data *data, char *cmd)
{
	char	*tmp;
	int		i;
	char	**paths;

	i = 0;
	tmp = ft_get_env("PATH", data->env);
	paths = ft_split_fd(tmp, ':');
	free(tmp);
	while (paths[i])
	{
		paths[i] = charjoinfree(paths[i], '/');
		tmp = ft_strjoin(paths[i], cmd);
		if (access(tmp, F_OK) == 0)
		{
			arr_free((void **)paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	arr_free((void **)paths);
	return (NULL);
}

//This function, change_fd_input_output, is responsible for updating the input and output file descriptors (in_fd and out_fd) of a command in the t_tab_cmd structure

int	change_fd_input_output(t_data *pntr, t_tab_cmd *tab_cmd, int *fd, int i)
{
	if (tab_cmd->file_in != -1)
		tab_cmd->in_fd = tab_cmd->file_in;
	else if (pntr->fd_before != -1 && i != 0)
		tab_cmd->in_fd = pntr->fd_before;
	if (tab_cmd->file_out != -1)
		tab_cmd->out_fd = tab_cmd->file_out;
	else if (fd[1] != -1 && pntr->cmdt_count - 1 != i)
		tab_cmd->out_fd = fd[1];
	return (0);
}

//This function, pipelines_redirect, is responsible for managing file descriptors and closing unnecessary pipes during the execution of a command within a pipeline

int	pipelines_redirect(t_data *pntr, int i, int *pip)
{
	if (dup2(pntr->cmdt[i].in_fd, STDIN_FILENO) > -1 && pntr->cmdt[i].in_fd != -1)
		close(pntr->cmdt[i].in_fd);
	if (pntr->cmdt[i].out_fd != -1)
		dup2(pntr->cmdt[i].out_fd, STDOUT_FILENO);
	close(pip[1]);
	if (pntr->fd_before != -1)
		close(pntr->fd_before);
	if (pntr->cmdt_count - 1 != i)
		pntr->fd_before = pip[0];
	else
		close(pip[0]);
	dup2(pntr->first_stdout, STDOUT_FILENO);
	dup2(pntr->first_stdin, STDIN_FILENO);
	if (pntr->cmdt[i].in_fd != -1)
		close(pntr->cmdt[i].in_fd);
	if (pntr->cmdt[i].out_fd != -1)
		close(pntr->cmdt[i].out_fd);
	if (pntr->cmdt[i].last_multiline)
	{
		unlink(pntr->cmdt[i].last_multiline);
		free(pntr->cmdt[i].last_multiline);
	}
	return (1);
}

//function finds the executable path of a command by looking in the current directory. If successful, it updates the command with the full path, and if not, it returns an error code. The function also handles memory allocation errors gracefully

int	find_path(t_data *pntr, t_tab_cmd *tab_cmd)
{
	char	*temporary;
	char	*result;

	if (pntr->path != NULL)
		return (1);
	if (tab_cmd->cmd[0] == '\0')
		return (1);
	temporary = ft_strdup("./");
	if (!temporary)
		return (error_out(pntr, "ft_strdup", 1) + 1);
	result = ft_strjoin(temporary, tab_cmd->cmd);
	if (!result)
		return (error_out(pntr, "ft_strjoin", 1) + 1);
	if (access(result, X_OK) == 0)
	{
		temporary = tab_cmd->cmd;
		tab_cmd->cmd = result;
		free(temporary);
		return (0);
	}
	free(result);
	return (1);
}