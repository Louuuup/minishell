/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:38:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/12/20 15:27:41 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_dup2(int fd, int std)
{
	int	err;

	err = dup2(fd, std);
	if (err == -1)
		ft_error(ERR_DUP);
	close(fd);
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
	int		working_idx;
	char	**paths;

	working_idx = -1;
	i = 0;
	tmp = ft_get_env("PATH", data->env);
	paths = ft_split(tmp, ':');
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
