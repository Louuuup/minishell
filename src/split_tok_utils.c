/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:16 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:16 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sgltok(t_countok *tok, char *str)
{
	tok->j++;
	while (str[tok->i + tok->j] && str[tok->i + tok->j] != '\'')
		tok->j++;
	tok->j++;
	return (1);
}

int	ft_dbltok(t_countok *tok, char *str)
{
	tok->j++;
	while (str[tok->i + tok->j] && str[tok->i + tok->j] != '\"')
		tok->j++;
	tok->j++;
	return (1);
}

int	ft_outtok(t_countok *tok, char *str)
{
	tok->j++;
	if (str[tok->i + tok->j] == '>')
		tok->j++;
	return (1);
}

int	ft_intok(t_countok *tok, char *str)
{
	tok->j++;
	if (str[tok->i + tok->j] == '<')
		tok->j++;
	return (1);
}

int	ft_wordtok(t_countok *tok, char *str)
{
	while (str[tok->i + tok->j] && !ft_strchr(C_FIND, str[tok->i + tok->j]))
		tok->j++;
	if (str[tok->i + tok->j] == '<' || str[tok->i + tok->j] == '>')
		return (1);
	if (str[tok->i + tok->j] == '\'')
	{
		tok->j++;
		while (str[tok->i + tok->j] != '\'')
			tok->j++;
		tok->j++;
	}
	if (str[tok->i + tok->j] == '\"')
	{
		tok->j++;
		while (str[tok->i + tok->j] != '\"')
			tok->j++;
		tok->j++;
	}
	if (str[tok->i + tok->j] && !ft_isspace(str[tok->i + tok->j]))
		ft_wordtok(tok, str);
	return (1);
}
