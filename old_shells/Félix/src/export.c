
#include "../include/minishell.h"
#include "../libft/libftps.h"

void exp_last_var(t_info *inf, int last_i, char ***new_env)
{
	int i;
	
	int j;
	i = 0;
	j = 1;
	while (inf->cmd_list->cmd[j])
	{
		while (inf->env[i])
		{
		if ((ft_strcmp_equal (inf->env[i], inf->cmd_list->cmd[j])))
			j++;
		if(!inf->cmd_list->cmd[j])
			break;
		i++;
		if (!inf->env[i] && inf->cmd_list->cmd[j])
		{	
			new_env[0][last_i] = ft_strdup(inf->cmd_list->cmd[j]);
			j++;
			last_i++;
		}
	}
	i = 0;
	}
}

int	ft_strcmp_equal(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	if (i == 0)
		return (FAILURE);
	if (s2[i] == '=' || (!s1[i] && !s2[i]) || (s1[i - 1] == '=' && s2[i - 1] == '='))
		return (SUCESS);
	return (FAILURE);
}

char **ft_exportvar(t_info *inf)
{
	int		i;
	int 	j;
	char	**new_env;

	j = 1;
	i = 0;
	if (!(new_env = malloc((env_len(inf->env) + env_len(inf->cmd_list->cmd)) * sizeof(char *))))
		return (NULL);
	ft_null_2darray(&new_env, (env_len(inf->env) + env_len(inf->cmd_list->cmd)));
	while (inf->env[i])	
	{
		while (inf->cmd_list->cmd[j])
		{
			if (ft_strcmp_equal (inf->env[i],inf->cmd_list->cmd[j]))
				new_env[i] = ft_strdup(inf->cmd_list->cmd[j]);
			j++;
		}
		if (!new_env[i])
			new_env[i] = ft_strdup(inf->env[i]);
		j = 1;
		i++;
	}
	exp_last_var(inf, i, &new_env);
	ft_free_2darray(inf->env);
	return (new_env);
}

int print_exp(char **alp_env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (alp_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while (alp_env[i][j] && alp_env[i][j - 1] != '=')
		{
			ft_putchar_fd(alp_env[i][j], 1);
			j++;
		}
		if (alp_env[i][j - 1] == '=')
		{
			ft_putchar_fd('"', 1);
			while (alp_env[i][j])
			{
				ft_putchar_fd(alp_env[i][j], 1);
				j++;
			}
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		j = 0;
		i++;
	}
	return (SUCESS);
}

int is_sorted_alpha(char **alp_env)
{
	int i;

	i = 0;
	while(alp_env[i] && alp_env[i + 1])
	{
		if (alp_env[i][0] > alp_env[i + 1][0])
			return (FAILURE);
		i++;
	}
	return (SUCESS);
}

int bbl_srt_alp(char **alp_env)
{
	int		i;
	char	*temp;

	while (!is_sorted_alpha(alp_env))
	{
		i = 0;
		while (alp_env[i] && alp_env[i + 1])
		{
			if (alp_env[i][0] > alp_env[i + 1][0])
			{
				temp = alp_env[i + 1];
				alp_env[i + 1] = alp_env[i];
				alp_env[i] = temp;
			}
			i++;
		}
	}
	return (SUCESS);
}

int ft_dupenv(char **dup_env, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		dup_env[i] = ft_strdup(env[i]);
		i++;
	}
	dup_env[i] = NULL;
	return (0);
}

int export(t_info *inf)
{
    char **alp_env;

    if (!inf->cmd_list->cmd[1])
    {
        alp_env = malloc((ft_x2strlen(inf->env) + 1) * (sizeof(char *)));
        ft_dupenv(alp_env, inf->env);
        bbl_srt_alp(alp_env);
        print_exp(alp_env);
		ft_free_2darray(alp_env);
    }
	else
		inf->env = ft_exportvar(inf);
	return (SUCESS);
}
