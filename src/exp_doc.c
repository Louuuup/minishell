/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:13:23 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:13:24 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checks_expdoc(char *str, int pos)
{
	if (!str)
		return (0);
	if (!str[pos])
		return (0);
	while (str[pos])
	{
		if (str[pos] == '$')
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
	if(exp->symb)
		exp_symb(exp);
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

	ft_init_exp(&exp, in, str);
	while (str[exp.i] == '$')
		incr_exp(&exp);
	if(str[exp.i])
	{
		if(!ft_strncmp(&str[exp.i], "?", 2) || !ft_strncmp(&str[exp.i], "?$", 2))
			incr_symb(str, &exp);
		if(!exp.symb)
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

int	ft_doc_exp(char *str, char **final)
{
	int	i;

	i = 0;
	while (str[i])
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
