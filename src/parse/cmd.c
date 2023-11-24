/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:35:41 by mkramer           #+#    #+#             */
/*   Updated: 2023/11/16 18:09:48 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_name(t_copy *copy)
{
	copy->redir.name = NULL;
	copy->redir.value = NULL;
	copy->redir.name = malloc(sizeof(char) * ft_strlen(copy->wc) + 1);
	if (!copy)
		return (-1);
	return (0);
}

int	quotes(t_copy *copy, int num)
{
	while (copy->wc[copy->i])
	{
		while (copy->wc[copy->i] == '\'')
		{
			num = single_quote(copy);
			if (num == -1)
				return (-1);
		}
		while (copy->wc[copy->i] == '"')
		{
			num = double_quote(copy, num);
			if (num == -1)
				return (-1);
		}
	}
	if (copy->wc[copy->i] == '\\')
		copy->i++;
	return (num);
}

int	redirect_env(t_copy *copy, int num)
{
	if (copy->wc[copy->i] && copy->wc[copy->i] == '$'
		&& (copy->i == 0 || copy->wc[copy->i - 1] != '\\'))
	{
		if (copy->wc[copy->i + 1] == '\\')
			copy->cmd[++copy->num] = copy->wc[copy->i];
		else
			num = env(copy, 0, 0, 1);
	}
	if ((copy->wc[copy->i] == '>' || copy->wc[copy->i] == '<')
		&& (copy->i == 0 || copy->wc[copy->i - 1] != '\\'))
		num = redirection(copy, 0);
	return (num);
}

char	*cmd(t_copy *copy, int num)
{
	while (copy->wc[copy->i] && copy->wc[copy->i] != 32)
	{
		num = -2;
		if ((copy->wc[copy->i] == '1' || copy->wc[copy->i] == '2')
			&& copy->wc[copy->i + 1] == '>'
			&& (!copy->cmd[0] || copy->wc[copy->i - 1] == 32))
			copy->i++;
		num = cmd_quoting(copy, num);
		num = cmd_redir_env(copy, num);
		if ((copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
			&& (copy->cmd[0] || (!copy->cmd[0] && (copy->wc[copy->i - 1] == '"'
						|| copy->wc[copy->i - 1] == '\'') && (copy->wc
						[copy->i - 2] == '"' || copy->wc[copy->i - 2] == '\''
						|| num == 1))))
			break ;
		if (copy->i < (int)ft_strlen(copy->wc) && ((copy->wc[copy->i] == '$'
					&& (copy->i == 0 || copy->wc[copy->i - 1] == '\\'))
				|| (copy->wc[copy->i] != '$' && num == -2)))
			copy->cmd[++copy->num] = copy->wc[copy->i];
		if (copy->i < (int)ft_strlen(copy->wc))
			copy->i++;
	}
	copy->cmd[copy->num + 1] = 0;
	return (copy->cmd);
}
