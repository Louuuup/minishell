#include "minishell.h"

void	index_sort(char **arr, int str_count, int *index)
{
	int		i;
	int		swapped;
	int		tmp;

	i = -1;
	swapped = 1;
	while (++i < str_count)
        index[i] = i;
	i = 0;
	while (arr[index[i]] && swapped)
	{
		swapped = 0;
		i = 0;
		while (i < str_count - 1)
		{
			// printf("i is %d\nstr is %s\n", i, arr[index[i]]);
			if (ft_strncmp(arr[index[i]], arr[index[i + 1]], ft_strlen(arr[index[i]])) > 0)
			{
				tmp = index[i];
				index[i] = index[i + 1];
				index[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
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
			if (write(fd, "\n", 1) == ERROR)
				ft_error(ERR_WRITE);
		}
		i++;
	}
}

void	built_env(t_data *data)
{
	int	i;

	i = -1;
	data->code_exit = 0;
	while (data->env[++i])
		ft_putendl_fd(data->env[i], STDOUT_FILENO);
	// print_env(data->env, fd_out);
}
