/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:58:04 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/22 18:10:27 by ycyr-roy         ###   ########.fr       */
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
void built_env(t_data *data)
{
	print_env(data->env,   1, EXPORT_PREFIX);
}

// void	built_export(char **args, int argc, int fd_out)
// {

// }
