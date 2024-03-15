/* ************************************************************************** */
/*								                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:02:00 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 13:18:33 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	index_sort(char **arr, int str_count, int *idx, int i)
{
	int		swapped;
	int		tmp;

	swapped = 1;
	while (++i < str_count)
		idx[i] = i;
	i = 0;
	while (arr[idx[i]] && swapped)
	{
		swapped = 0;
		i = 0;
		while (i < str_count - 1)
		{
			if (ft_strncmp(arr[idx[i]], arr[idx[i + 1]], \
			ft_strlen(arr[idx[i]])) > 0)
			{
				tmp = idx[i];
				idx[i] = idx[i + 1];
				idx[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

int	print_export(char **env, int fd)
{
	int	i[2];
	int	equal;
	int	*index;

	index = gc_calloc(arr_len(env) + 1, sizeof(int));
	i[0] = 0;
	index_sort(env, arr_len(env), index, -1);
	while (env && env[i[0]] != NULL)
	{
		i[1] = 0;
		ft_putstr_fd(EXPORT_PREFIX, fd);
		equal = find_symbol('=', env[index[i[0]]]);
		while (env[index[i[0]]][i[1]] != '\0')
		{
			ft_putchar_fd(env[index[i[0]]][i[1]], fd);
			if (i[1] > 0 && i[1] == equal)
				ft_putchar_fd('"', fd);
			i[1]++;
		}
		if (equal)
			ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
		i[0]++;
	}
	return (NO_ERROR);
}

static void	env_addline(char *str)
{
	int		i;
	t_data	*data;
	char	**new_env;
	char	*tmp;

	i = 0;
	data = get_data();
	while (data->env[i])
		i++;
	new_env = gc_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	tmp = ft_strtrim(str, " ");
	new_env[i] = gc_strdup(tmp);
	tmp = free_null(tmp);
	gc_free_one(data->memblock, data->env);
	data->env = new_env;
}

int	b_export(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*var;

	i = 1;
	if (cmd->ac < 1)
		return (print_export(data->env, cmd->fd_out));
	else
	{
		while (cmd->cmd[i])
		{
			if (export_valid(cmd->cmd[i]) == FALSE)
				error_str_file("export: not a valid identifier :", \
				(cmd->cmd[i]));
			var = var_name(cmd->cmd[i]);
			if (get_var(data->env, var) == NULL)
				env_addline(cmd->cmd[i]);
			else if (find_symbol('=', cmd->cmd[i]) && \
			get_var(data->env, var) != NULL)
				set_var(data->env, var, var_value(cmd->cmd[i]));
			i++;
			var = free_null(var);
		}
	}
	return (NO_ERROR);
}
