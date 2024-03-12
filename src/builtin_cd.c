/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:45 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/11 16:56:47 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_chdir(char *pwd)
{
	if (chdir(pwd) == ERROR)
		return (error_str("cd: error"));
	return (NO_ERROR);
}

int	b_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	if (access(cmd->cmd[1], F_OK) != ERROR)
		return (cd_fullpath(cmd->cmd[1]) == 1);
	pwd = NULL;
	oldpwd = get_var(get_data()->env, "PWD");
	if (cmd->ac > 0)
	{
		pwd = gc_strjoin(oldpwd, "/");
		pwd = gc_strjoin(pwd, cmd->cmd[1]);
		if (DEBUG_ON)
			printf("(b_cd) pwd: %s\n", pwd);
	}
	else
		pwd = get_var(get_data()->env, "HOME");
	if (access(pwd, F_OK) != ERROR)
	{
		if (chdir(pwd) == ERROR)
			return (error_str("cd: error"));
	}
	else
		return (error_str_code("cd: no such file or directory\n", pwd, 1));
	set_var(get_data()->env, "OLDPWD", oldpwd);
	set_var(get_data()->env, "PWD", getcwd(NULL, 0));
	return (NO_ERROR);
}

int	b_pwd(t_cmd *cmd)
{
	ft_putstr_fd(get_var(get_data()->env, "PWD"), cmd->fd_out);
	ft_putchar_fd('\n', cmd->fd_out);
	return (NO_ERROR);
}
