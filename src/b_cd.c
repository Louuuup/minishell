#include "minishell.h"

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
	else
		my_error(ERR_CD);
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
