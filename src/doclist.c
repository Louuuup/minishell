/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doclist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:48 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:10:48 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_doc	*ft_lstnewdoc(char *str, int qts)
{
	t_doc	*elm;

	elm = gc_calloc(1, sizeof(t_doc));
	if (!elm)
		return (NULL);
	elm->eof = gc_strdup(str);
	elm->next = NULL;
	if (qts)
		elm->expand = true;
	return (elm);
}

t_doc	*ft_doclast(t_doc *lst)
{
	while (lst && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_docadd_back(t_doc **lst, t_doc *new_cmd)
{
	t_doc	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp = ft_doclast(*lst);
		temp->next = new_cmd;
		temp->next->index = 1 + temp->index;
		return ;
	}
	*lst = new_cmd;
	new_cmd->index = 0;
}

void	ft_cleardoclst(t_doc **lst)
{
	t_doc	*temp;
	t_data	*data;

	data = get_data();
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			if (*lst)
			{
				unlink((*lst)->name);
				gc_free_one(get_data()->memblock, (*lst)->name);
				gc_free_one(get_data()->memblock, (*lst)->eof);
				gc_free_one(data->memblock,*lst);
			}
			*lst = temp;
		}
	}
	lst = NULL;
}

void	ft_cleardoctrlc(t_doc **lst)
{
	t_doc	*temp;
	t_data	*data;

	data = get_data();
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			if (*lst)
			{
				unlink((*lst)->name);
				gc_free_one(get_data()->memblock, (*lst)->eof);
				gc_free_one(data->memblock,*lst);
			}
			*lst = temp;
		}
	}
	lst = NULL;
}
