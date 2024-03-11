/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:20 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:14:20 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_exp(t_expand *exp, int in, char *str)
{
	exp->str = str;
	exp->i = in;
	exp->j = 0;
	exp->init = (in - 1);
	exp->name = gc_malloc(ft_strlen(str) + 1 * sizeof(char));
	exp->symb = false;
	return (1);
}

int	ft_checksecexp(char *str, int pos)
{
	t_ibool	i;

	if (!str)
		return (0);
	exp_qtes_bool(str, &i, pos);
	if (!str[pos])
		return (0);
	while (str[pos])
	{
		if (str[pos] == '\'')
			ft_sglbool(&i.single, &i.dbl);
		if (str[pos] == '"')
			ft_dblbool(&i.single, &i.dbl);
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

int	ft_expcat(t_expand *exp, char **final)
{
	t_data	*data;

	data = get_data();
	exp->var = get_var(data->env, exp->name);
	exp->h = 0;
	exp->tmp = gc_malloc(explencheck(exp->str, exp->var) + 1 * (sizeof(char)));
	exp_early_str(exp);
	if (exp->symb)
		exp_symb(exp);
	else if (!exp->var)
		exp_novar(exp);
	else if (exp->var)
		exp_var(exp);
	if (ft_checksecexp(exp->tmp, exp->j))
		ft_expand(ft_checksecexp(exp->tmp, exp->j), exp->tmp, final);
	else
		*final = gc_strdup(exp->tmp);
	gc_free_one(data->memblock, exp->tmp);
	gc_free_one(data->memblock, exp->name);
	return (0);
}

int	ft_expand(int in, char *str, char **final)
{
	t_expand	exp;

	ft_init_exp(&exp, in, str);
	while (str[exp.i] == '$')
		incr_exp(&exp);
	if (str[exp.i])
	{
		if (!ft_strncmp(&str[exp.i], "?", 1) || \
		!ft_strncmp(&str[exp.i], "?$", 2))
			incr_symb(str, &exp);
		if (!exp.symb)
		{
			while (str[exp.i] && (ft_isalnum(str[exp.i]) || str[exp.i] == '_'))
				exp.name[exp.j++] = str[exp.i++];
			exp.name[exp.j] = '\0';
		}
		ft_expcat(&exp, final);
	}
	else
		*final = gc_strdup(str);
	return (1);
}

int	ft_expansion(char *str, char **final)
{
	t_ibool	i;

	i.i = 0;
	i.single = false;
	i.dbl = false;
	while (str[i.i])
	{
		if (str[i.i] == '$' && i.single == false)
		{
			while (str[i.i] == '$' && str[i.i])
				i.i++;
			return (ft_expand((i.i), str, final));
		}
		if (str[i.i] == '\'')
			ft_sglbool(&i.single, &i.dbl);
		if (str[i.i] == '"')
			ft_dblbool(&i.single, &i.dbl);
		i.i++;
	}
	*final = gc_strdup(str);
	return (0);
}
