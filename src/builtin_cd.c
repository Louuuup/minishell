/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:45 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/13 22:17:35 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*slash_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = gc_strjoin(s1, "/");
	tmp = gc_strjoin(tmp, s2);
	return (tmp);
}

static int	error_code(int error, t_cmd *cmdt)
{
	if (error == ERROR)
		return (error_str_code("cd: unable to access ", cmdt->cmd[1], error));
	return (NO_ERROR);
}

int	b_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	int		error;

	error = NO_ERROR;
	pwd = NULL;
	oldpwd = getcwd(NULL, 42);
	if (cmd->ac > 0)
		pwd = slash_join(oldpwd, cmd->cmd[1]);
	else
		pwd = get_var(get_data()->env, "HOME");
	if (access(cmd->cmd[1], F_OK) != ERROR)
		error = chdir(cmd->cmd[1]);
	else if (access(pwd, F_OK) != ERROR)
		error = chdir(pwd);
	else
	{
		oldpwd = free_null(oldpwd);
		return (error_str_code(cmd->cmd[1], " : no such file or dir\n", 1));
	}
	set_var(get_data()->env, "OLDPWD", oldpwd);
	set_var(get_data()->env, "PWD", getcwd(NULL, 0));
	if (oldpwd)
		oldpwd = free_null(oldpwd);
	return (error_code(error, cmd));
}

int	b_pwd(t_cmd *cmd)
{
	ft_putstr_fd(get_var(get_data()->env, "PWD"), cmd->fd_out);
	ft_putchar_fd('\n', cmd->fd_out);
	return (NO_ERROR);
}
