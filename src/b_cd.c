#include "minishell.h"

void	built_cd(char **args, int argc)
{
	char	*new_path;
	char	*pwd;
	int		err;

	err = 0;
	pwd = getcwd(NULL, 0);
	pwd = charjoinfree(pwd, '/');
	new_path = ft_strjoin(pwd, args[1]);
	if (argc > 2)
		my_error(ERR_CD_ARGS);
	if (access(new_path, F_OK) != ERROR)
		err = chdir(new_path);
	else if (access(args[1], F_OK) != ERROR)
		err = chdir(args[1]);
	else
		my_error(ERR_CD);
	if (new_path)
		free(new_path);
	if (pwd)
		free(pwd);
	if (err == ERROR)
		my_error(ERR_CD);
}

void	build_pwd(t_data *pnt)
{
	char *path;

	pnt->code_exit = 0;
	path = getcwd(NULL, 0);
	if (path)
		ft_printf_fd(STDOUT_FILENO, "%s\n", path);
	free(path);
}

// int	build_cd(t_data *pnt, t_tab_cmd *tab_cmd)
// {
// 	char	*way
// }