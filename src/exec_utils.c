/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:38:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/12/15 17:04:01 by ycyr-roy         ###   ########.fr       */
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
	int		i;
	char	*out;

	i = 0;
	while (env[i])
	{

		if (ft_strnstr(env[i], str, ft_strlen(str)) && find_symbol('=', env[i]))
			break ;
		i++;
	}
	out = ft_calloc(ft_strlen(env[i]) - ft_strlen(str), sizeof(char));

	return (NULL);

}

// int	cmd_exists(t_data *data, char *cmd)
// {
// 	char **arr;
// 	ft_get_env("PATH", );


// }
