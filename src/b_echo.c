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
