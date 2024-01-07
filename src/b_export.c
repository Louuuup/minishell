#include "minishell.h"

static int	export_valid(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return(FALSE);
		i++;
	}
	return (TRUE);
}
int	var_in_env(char *str)
{
	int		i;
	int		limit;
	t_data *data;

	i = 0;
	data = get_data();
	limit = 0;
	while (str[limit] && str[limit] != '=')
		limit++;
	while(data->env[i])
	{
		if (ft_strncmp(str, data->env[i], limit) == 0)
		{
			data->env[i] = str;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static void	env_addline(char *str)
{
	int i;
	t_data *data;
	char **new_env;

	i = 0;
	data = get_data();
	if (export_valid(str) == FALSE)
		my_error(ERR_EXPORT);
	else if (var_in_env(str) == TRUE)
		return ;
	while (data->env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		new_env[i] = data->env[i];
		i++;
	}
	new_env[i] = ft_strdup(str);
	free(data->env);
	data->env = new_env;
}

void	print_export(char **env, int fd)
{
	int	i;
	int	j;
	int	equal;
	int	index[arr_len(env)];

	i = 0;
	printf("str_count = %d\n", arr_len(env));
	index_sort(env, arr_len(env), index);
	while (env[i] != NULL)
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

void	built_export(char **args, int argc, int fd_out)
{
	int i;

	i = 1;
	if (argc < 2)
		return (print_export(get_data()->env, fd_out));
	while (i < argc)
	{
		env_addline(args[i]);
		i++;
	}
}
