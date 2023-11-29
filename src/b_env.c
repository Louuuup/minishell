#include "minishell.h"

static int	find_symbol(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	print_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (find_symbol('=', env[i]))
		{
			ft_putstr_fd(env[i], fd);
			write(fd, "\n", 1);
		}
		i++;
	}
}

void	print_export(char **env, int fd)
{
	int	i;
	int	j;
	int	equal;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		ft_putstr_fd(EXPORT_PREFIX, fd);
		equal = find_symbol('=', env[i]);
		while (env[i][j] != '\0')
		{
			ft_putchar_fd(env[i][j], fd);
			if (j > 0 && j == equal)
				ft_putchar_fd('"', fd);
			j++;
		}
		if (equal)
			ft_putchar_fd('"', fd);
		write(fd, "\n", 1);
		i++;
	}
}

void built_env(t_data *data, int fd_out)
{
	print_env(data->env, fd_out);
}
