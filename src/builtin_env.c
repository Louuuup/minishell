/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:52 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/15 12:37:44 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *var)
{
	int	i;
	int	j;

	i = 0;
	if (DEBUG_ON)
		printf("(get_var) var: %s\n", var);
	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(get_data()->code_exit));
	while (env && env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], var, j) == 0 && ft_strlen(var) == j)
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

char	*set_var(char **env, char *var, char *value)
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	if (!get_data()->env || !var || !get_var(get_data()->env, var))
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		if (ft_strncmp(env[i], var, j) == 0)
		{
			new_var = gc_strjoin(var, "=");
			new_var = gc_strjoin(new_var, value);
			gc_free_one(get_data()->memblock, env[i]);
			env[i] = new_var;
			return (env[i]);
		}
		get_data()->code_exit = 0;
		i++;
	}
	return (NULL);
}

char	**rm_var(t_data *data, char *var, char *alt_var)
{
	int		i[2];
	int		j;
	char	**new_env;

	if (!data->env || !var || !get_var(data->env, var))
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	new_env = gc_calloc(arr_len(data->env), sizeof(char *));
	while (new_env && data->env[++i[0]])
	{
		j = 0;
		alt_var = ft_strjoin(var, "=");
		while (data->env[i[0]][j] && data->env[i[0]][j] != '=')
			j++;
		if (ft_strncmp(data->env[i[0]], alt_var, j + 1) != 0)
			new_env[++i[1]] = data->env[i[0]];
		else
		{
			gc_free_one(data->memblock, data->env[i[0]]);
		}
		alt_var = free_null(alt_var);
	}
	return (new_env);
}

char	**add_var(char **env, char *var, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = gc_calloc(i + 2, sizeof(char *));
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		gc_free_one(get_data()->memblock, env[i]);
		i++;
	}
	new_env[i] = ft_strjoin(var, "=");
	new_env[i] = ft_strjoin(new_env[i], value);
	free(env);
	env = new_env;
	return (NULL);
}

int	b_env(t_cmd *cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = get_data()->env;
	if (!env)
		return (error_str("env: cannot find environment\n"));
	while (env[i])
	{
		if (find_symbol('=', env[i]))
		{
			ft_putstr_fd(env[i], cmd->fd_out);
			ft_putchar_fd('\n', cmd->fd_out);
		}
		i++;
	}
	return (NO_ERROR);
}
