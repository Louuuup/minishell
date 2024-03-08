/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:39 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:14:40 by ycyr-roy         ###   ########.fr       */
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

t_data	*init_all(char **envp, char *argv[], int argc)
{
	int i;
	t_data *data;

	(void)argv;
	(void)argc;
	data = get_data();
	i = 0;
	if (DEBUG_ON)
		printf("(init_all) start\n");
	data->env = gc_calloc(arr_len(envp) + 1, sizeof(char *));
	while (envp[i])
	{
		data->env[i] = gc_strdup(envp[i]);
		i++;
	}
	data->code_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	shlvl(data);
	return (data);
}
