/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:13:21 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/13 20:51:26 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_in != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	return (NO_ERROR);
}

static char	*cmd_access(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	if (*cmd == '\0')
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
	{
		return (gc_strdup(cmd));
	}
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			full_path = gc_strdup(tmp);
			tmp = free_null(tmp);
			return (full_path);
		}
		tmp = free_null(tmp);
		i++;
	}
	return (NULL);
}

int	command_valid(t_cmd *cmdt, char *cmd, int i)
{
	char	*cmd_path;
	char	**paths;

	if (access(cmdt->cmd[0], F_OK | X_OK) == 0)
	{
		cmdt->path = gc_strdup(cmdt->cmd[0]);
		return (TRUE);
	}
	cmd_path = get_var(get_data()->env, "PATH");
	if (!cmd_path)
		return (FALSE);
	paths = ft_split(cmd_path, ':');
	if (!paths)
		return (FALSE);
	cmd_path = paths[0];
	paths[0] = ft_strtrim(paths[0], "PATHS=");
	cmd_path = free_null(cmd_path);
	i = -1;
	while (paths[++i])
		paths[i] = charjoinfree(paths[i], '/');
	cmdt->path = cmd_access(cmd, paths);
	paths = arr_free((void **)paths);
	if (!cmdt->path)
		return (FALSE);
	return (TRUE);
}

//gets command from index
t_cmd	*get_cmd(t_data *data, int idx)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->index == idx)
			return (cmd);
		cmd = cmd->next;
	}
	return (NULL);
}
