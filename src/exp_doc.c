#include "minishell.h"

int	ft_checks_expdoc(char *str, int pos)
{
	if (!str)
		return (0);
	if (!str[pos])
		return (0);
	while (str[pos])
	{
		if (str[pos] == '$' && !i.single)
		{
			while (str[pos] == '$')
			{
				pos++;
				return (pos);
			}
		}
		pos++;
	}
	return (0);
}

int	ft_expcatdoc(t_expand *exp, char **final)
{
	t_data	*data;

	data = get_data();
	exp->var = get_var(data->env, exp->name);
	exp->h = 0;
	exp->tmp = gc_malloc(explencheck(exp->str, exp->var) + 1 * (sizeof(char)));
	exp_early_str(exp);
	if (!exp->var)
		exp_novar(exp);
	else if (exp->var)
		exp_var(exp);
	if (ft_checks_expdoc(exp->tmp, exp->j))
		ft_expand(ft_checksecexp(exp->tmp, exp->j), exp->tmp, final);
	else
		*final = gc_strdup(exp->tmp);
	gc_free_one(data->memblock, exp->tmp);
	gc_free_one(data->memblock, exp->name);
	return (0);
}

int	ft_expandoc(int in, char *str, char **final)
{
	t_expand	exp;

	exp.str = str;
	exp.i = in;
	exp.j = 0;
	exp.init = (in - 1);
	exp.name = gc_malloc(ft_strlen(str) + 1 * sizeof(char));
	while (str[exp.i + 1] == '$')
	{
		exp.i++;
		exp.init++;
	}
	while (str[exp.i] && (ft_isalnum(str[exp.i]) || str[exp.i] == '_'))
		exp.name[exp.j++] = str[exp.i++];
	exp.name[exp.j] = '\0';
	ft_expcatdoc(&exp, final);
	return (1);
}

int	ft_doc_exp(char *str, char **final)
{
	int	i;

	i = 0;
	while (str[i.i])
	{
		if (str[i] == '$')
		{
			while (str[i] == '$' && str[i])
				i++;
			return (ft_expandoc(i, str, final));
		}
		i++;
	}
	*final = gc_strdup(str);
	return (0);
}
