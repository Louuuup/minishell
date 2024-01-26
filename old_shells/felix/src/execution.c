

#include "../include/minishell.h"
#include "../include/execution.h"

char	*ft_strjoinslash(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (ptr == 0)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '/';
	i++;
	while (s2[j])
	{
		ptr[i + j] = s2 [j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

char	*pathfinder(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != 'P')
			j++;
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

void	free_cmdpath(char **s_path, char **s_cmd)
{
	ft_free(s_cmd);
	ft_free(s_path);
}

char	*truepath(char *cmd, char **env)
{
	int		i;
	char	**s_path;
	char	**s_cmd;
	char	*path;

	i = -1;
	s_path = ft_split(pathfinder(env), ':');
	s_cmd = ft_split(cmd, ' ');
	if (access(s_cmd[0], F_OK | X_OK) == 0)
	{
		ft_free(s_path);
		return (s_cmd[0]);
	}
	while (s_path[++i])
	{
		path = ft_strjoinslash(s_path[i], s_cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_cmdpath(s_path, s_cmd);
			return (path);
		}
		free(path);
	}
	free_cmdpath(s_path, s_cmd);
	return (NULL);
}

int	ft_execute(t_info *inf)
{
	char	*path;

	/*if (inf->cmd_list->built_in == true)
	{
		ft_executebuiltin(inf);
		return (SUCESS);
	}*/
	path = truepath(inf->cmd_list->cmd[0], inf->env);
	if (!path)
	{
		ft_putstr_fd("Command not found :", 2);
		ft_putendl_fd(inf->cmd_list->cmd[0], 2);
		ft_free(inf->cmd_list->cmd);
		return (FAILURE);
	}
	inf->cmd_list->pid = fork();
	if (inf->cmd_list->pid == 0)
	{
		printf("%d\n", inf->cmd_list->fd_in);
		printf("%d\n", inf->cmd_list->fd_out);
		dup2(inf->cmd_list->fd_in, STDIN_FILENO);
		dup2(inf->cmd_list->fd_out, STDOUT_FILENO);
		close(inf->cmd_list->fd_out);
		close(inf->cmd_list->fd_in);
		if (inf->cmd_list->built_in == true)
		{
			ft_executebuiltin(inf);
			exit(0);
		}
		else
			execve(path, inf->cmd_list->cmd, inf->env);
	}
	return (SUCESS);
}
