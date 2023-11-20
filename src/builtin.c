/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:56:23 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/20 15:42:21 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_flag(char **args, int argc)
{
	int	flagged;
	int i;

	i = 1;
	flagged = 0;
	if (argc >= 3 && ft_strlen(args[1]) >= 2 && args[1][0] == '-')
	{
		flagged = 1;
		while(args[1][i])
		{
			if (args[1][i] != 'n')
				return (0);
			i++;
		}
	}
	return (flagged);
}

void	built_echo(char **args, int argc, int fd_out)
{
	int	flagged;
	int i;

	flagged = echo_flag(args, argc);
	i = 1 + flagged;
	while (i < argc)
	{
		ft_putstr_fd(args[i], fd_out);
		i++;
		if (i < argc)
			ft_putchar_fd(' ', fd_out);
	}
	if (flagged)
		ft_putchar_fd('$', fd_out);
	ft_putchar_fd('\n', fd_out);

}
// static int		is_full_path(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '/')
// 		i++;
// 	while (str[i] == '/')
// 		i++;
// 	if (str[i])
// 		return (1);
// 	return (0);
// }

void	built_cd(char **args, int argc, int fd_out)
{
	char *new_path;
	char *pwd;

	(void)fd_out;
	pwd = getcwd(NULL, 0);
	pwd = charjoinfree(pwd, '/');
	new_path = ft_strjoin(pwd, args[1]);
	if (argc > 2)
		my_error(ERR_CD_ARGS);
	if (access(new_path, F_OK) != ERROR)
		chdir(new_path);
	else if (access(args[1], F_OK) != ERROR)
		chdir(args[1]);
	if (new_path)
		free(new_path);
	if (pwd)
		free(pwd);
}

void	build_pwd(int fd_out)
{
	char *path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, fd_out);
	ft_putchar_fd('\n', fd_out);
}
