/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_sort_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:21 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:21 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkqtesdoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int	tok_doc(char *str, t_idtok *id, t_cmd *tmp)
{
	t_doc		*doc;
	int			qts;

	qts = checkqtesdoc(str);
	ft_docadd_back(&tmp->doc, ft_lstnewdoc(str, qts));
	doc = tmp->doc;
	while (doc->next)
		doc = doc->next;
	doc->eof = gc_strdup(str);
	ft_removeqte(doc->eof);
	tmp->in_flag = REDIR_HEREDOC;
	id->here = false;
	return (1);
}
