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

void	print_export(char **env, int fd)
{
	int	i;
	int	j;
	int	equal;
	int	index[arr_len(env)];

	i = 0;
	index_sort(env, arr_len(env), index);
	while (env && env[i] != NULL)
	{
		j = 0;
		ft_putstr_fd(EXPORT_PREFIX, fd);
		equal = find_symbol('=', env[index[i]]);
		while (env[index[i]][j] != '\0')
		{
			ft_putchar_fd(env[index[i]][j], fd);
			if (j > 0 && j == equal)
				ft_putchar_fd('"', fd);
			j++;
		}
		if (equal)
			ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}

void    b_export(t_cmd *cmd)
{
    int		i;
    t_data	*data;
	char	*var;

    i = 1;
    data = get_data();
    if (cmd->ac < 2)
        return (print_export(data->env, cmd->fd_out));
    else
    {
        while (cmd->cmd[i])
        {
			if (export_valid(cmd->cmd[i]) == FALSE)
			{
				error_str("export: not a valid identifier");
				return ;
			}
			var = var_name(cmd->cmd[i]);
            if (find_symbol('=', cmd->cmd[i]) && get_var(data->env, var) == NULL)
                data->env = add_var(data->env, cmd->cmd[i], NULL);
			else if (find_symbol('=', cmd->cmd[i]) && get_var(data->env, var) != NULL)
				set_var(data->env, var, cmd->cmd[i]);
            i++;
			var = free_null(var);
        }
    }
}