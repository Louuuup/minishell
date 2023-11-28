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

int	export_valid(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return(FALSE);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (TRUE);
}

// static void	export_new(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (export_valid(str) == TRUE)
// 	{

// 	}
// 	else
// 		return ;

// }

void	built_export(char **args, int argc, int fd_out)
{
	int i;

	i = 1;
	(void)args;
	if (argc < 2)
		return (print_env(get_data()->env, fd_out, EXPORT_PREFIX));
	while (i < argc)
	{

	}
}
