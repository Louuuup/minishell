#include "minishell.h"

int	explencheck(char *str, char *var)
{
	if (!str && !var)
		return (0);
	if (!var)
		return (ft_strlen(str) + 1);
	else
		return (ft_strlen(str) + ft_strlen(var) + 1);
}

int	exp_early_str(t_expand *exp)
{
	exp->tmp[exp->h] = '\0';
	while (exp->h < exp->init)
	{
		exp->tmp[exp->h] = exp->str[exp->h];
		exp->h++;
		exp->tmp[exp->h] = '\0';
	}
	return (1);
}

int	exp_novar(t_expand *exp)
{
	if (!exp->var)
	{
		exp->i = ft_strlen(exp->tmp);
		exp->j = (exp->h + ft_strlen(exp->name) + 1);
		ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], \
			((size_t)ft_strlen(&exp->str[exp->j]) + 1));
		exp->j = exp->h;
	}
	return (1);
}

int	exp_var(t_expand *exp)
{
	ft_strlcat(&exp->tmp[exp->h], exp->var, ((size_t)ft_strlen(exp->var) + 2));
	exp->i = ft_strlen(exp->tmp);
	exp->j = (exp->h + ft_strlen(exp->name) + 1);
	ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], \
		((size_t)ft_strlen(&exp->str[exp->j]) + 1));
	exp->j = (exp->h + ft_strlen(exp->var));
	return (1);
}
