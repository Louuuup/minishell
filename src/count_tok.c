/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:50 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:10:50 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sglcount(t_countok *tok, char *str)
{
	tok->count++;
	tok->i++;
	while (str[tok->i] && str[tok->i] != '\'')
		tok->i++;
	tok->i++;
	return (1);
}

int	ft_dblcount(t_countok *tok, char *str)
{
	tok->count++;
	tok->i++;
	while (str[tok->i] && str[tok->i] != '\"')
		tok->i++;
	tok->i++;
	return (1);
}

int	ft_outcount(t_countok *tok, char *str)
{
	tok->count++;
	tok->i++;
	if (str[tok->i] == '>')
		tok->i++;
	return (1);
}

int	ft_incount(t_countok *tok, char *str)
{
	tok->count++;
	tok->i++;
	if (str[tok->i] == '<')
		tok->i++;
	return (1);
}

int	ft_tokcount(t_countok *tok, char *str)
{
	while ((str[tok->i] && !ft_strchr(C_FIND, str[tok->i])))
		tok->i++;
	if (str[tok->i] == '<' || str[tok->i] == '>')
		return (1);
	if (str[tok->i] == '\'')
	{
		tok->i++;
		while (str[tok->i] != '\'')
			tok->i++;
		tok->i++;
	}
	if (str[tok->i] == '\"')
	{
		tok->i++;
		while (str[tok->i] != '\"')
			tok->i++;
		tok->i++;
	}
	if (str[tok->i] && !ft_isspace(str[tok->i]))
		ft_tokcount(tok, str);
	return (1);
}
