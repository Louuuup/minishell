#include "minishell.h"

void	b_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	oldpwd = get_var(get_data()->env, "PWD");
	if (cmd->ac >= 1)
	{
		pwd = gc_strjoin(oldpwd, "/");
		pwd = gc_strjoin(pwd, cmd->cmd[1]);
	}
	else
		pwd = get_var(get_data()->env, "HOME");
	if (access(pwd, F_OK) != ERROR)
	{
		if (chdir(pwd) == ERROR)
			error_str_ret("cd: error");
		else
			get_data()->code_exit = 0;
		return ;
	}
	else
		error_str_ret("cd: no such file or directory\n");
}

void	b_pwd(t_cmd *cmd)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		get_data()->code_exit = 1;
	ft_putstr_fd(pwd, cmd->fd_out);
	ft_putchar_fd('\n', cmd->fd_out);
	get_data()->code_exit = 0;
}
