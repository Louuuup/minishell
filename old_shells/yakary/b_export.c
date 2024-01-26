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
	index_sort(env, arr_len(env), index);
	printf("(print_export) -> arr_len(env) = %d\n", arr_len(env)); //debug

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

void	built_export(t_data *data, t_tab_cmd *cmd, int fd_out)
{
	int i;
	i = 0;
	printf("(built_export) -> cmd = %s\n", cmd->cmd);
	if (data->env)
		printf("(built_export) -> env exists.\n");
	else
		printf("(built_export) -> env does not exist.\n");
	printf("(built_export) -> num_args = %d\n", cmd->num_args);
	printf("(build_export) -> in_fd = %d\n", cmd->in_fd); //debug
	printf("(build_export) -> out_fd = %d\n", cmd->out_fd); //debug
	if (cmd->num_args < 2)
	{
		if (data->env != NULL)
		{
			if (cmd->out_fd > 1)
				return (print_export(data->env, cmd->out_fd));
			else
				return (print_export(data->env, fd_out));

		}
		else
			my_error("Empty environnement\n");
	}
	while (i < cmd->num_args)
	{
		env_addline(cmd->args[i]);
		i++;
	}
}
