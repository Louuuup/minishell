/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:39 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/15 12:32:21 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_data *data)
{
	char	*shlvl;
	int		lvl;

	shlvl = get_var(data->env, "SHLVL");
	if (shlvl)
	{
		lvl = ft_atoi(shlvl);
		lvl++;
		shlvl = ft_itoa(lvl);
		set_var(data->env, "SHLVL", shlvl);
		free_null(shlvl);
	}
	else
		set_var(data->env, "SHLVL", "1");
}

void	env_init(t_data *data)
{
	data->env = gc_calloc(5, sizeof(char *));
	data->env[0] = gc_strdup("SHLVL=1");
	data->env[1] = gc_strdup("PWD=");
	data->env[2] = gc_strdup("OLDPWD=");
	data->env[3] = gc_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	data->env[4] = NULL;
}

t_data	*init_all(char **envp, char *argv[], int argc)
{
	int		i;
	t_data	*data;

	(void)argv;
	(void)argc;
	data = get_data();
	i = 0;
	if (envp[0] == NULL)
		env_init(data);
	else
		data->env = gc_calloc(arr_len(envp) + 1, sizeof(char *));
	while (envp && envp[i])
	{
		data->env[i] = gc_strdup(envp[i]);
		i++;
	}
	data->code_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	shlvl(data);
	return (data);
}
