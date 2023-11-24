/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:58:04 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/24 17:08:01 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env, int fd, char *prefix)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (prefix)
			ft_putstr_fd(prefix, fd);
		ft_putstr_fd(env[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}

void built_env(t_data *data, int fd_out)
{
	print_env(data->env, fd_out, EXPORT_PREFIX);
}

static void	export_new(char *str)
{
	int i;

	i = 0;
	if (isalpha(str[i]) || str[i] == '_')
		;
	while(str[i])
}

void	built_export(char **args, int argc, int fd_out)
{
	int i;

	i = 1;
	if (argc < 2)
		return (print_env(get_data()->env, fd_out, EXPORT_PREFIX));
	while (i < argc)
	{

	}
}
