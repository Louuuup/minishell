/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:01:45 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/13 20:54:56 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	int		error;

	error = NO_ERROR;
	pwd = NULL;
	oldpwd = get_var(get_data()->env, "PWD");
	if (cmd->ac > 0)
	{
		pwd = gc_strjoin(oldpwd, "/");
		pwd = gc_strjoin(pwd, cmd->cmd[1]);
	}
	else
		pwd = get_var(get_data()->env, "HOME");
	if (access(cmd->cmd[1], F_OK) != ERROR)
		error = chdir(cmd->cmd[1]);
	else if (access(pwd, F_OK) != ERROR)
		error = chdir(pwd) == ERROR;
	else
		error_str("cd: no such file or directory\n");
	if (error == ERROR)
		return (error_str_code("cd: unable to access ", cmd->cmd[1], 1));
	set_var(get_data()->env, "OLDPWD", oldpwd);
	set_var(get_data()->env, "PWD", getcwd(NULL, 0));
	return (NO_ERROR);
}

int	b_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
	{
		perror("Minishell");
		return (ERROR);
	}
	printf("%s\n", pwd);
	return (NO_ERROR);
}
