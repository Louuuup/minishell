/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expcat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:22 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:33:39 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_symb(t_expand *exp)
{
	ft_strlcat(&exp->tmp[exp->h], exp->var, ((size_t)ft_strlen(exp->var) + 2));
	exp->i = ft_strlen(exp->tmp);
	exp->j = (exp->h + ft_strlen(exp->name) + 1);
	ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], \
		((size_t)ft_strlen(&exp->str[exp->j]) + 1));
	exp->j = (exp->h + ft_strlen(exp->var));
	free (exp->var);
	return (1);
}

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
		if (!ft_strlen(exp->name))
			exp->j = exp->h;
		else
			exp->j = (exp->h + ft_strlen(exp->name) + 1);
		ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], \
			((size_t)ft_strlen(&exp->str[exp->j]) + 1));
		if (!ft_strlen(exp->name))
			exp->j = exp->h + 1;
		else
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
