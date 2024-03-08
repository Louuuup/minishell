/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:41 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:14:41 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstnewcmd(void)
{
	t_cmd	*elm;

	elm = gc_calloc(1, sizeof(t_cmd));
	if (!elm)
		return (NULL);
	elm->fd_in = STDIN_FILENO;
	elm->fd_out = STDOUT_FILENO;
	return (elm);
}

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	while (lst && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp = ft_cmdlast(*lst);
		temp->next = new_cmd;
		temp->next->index = 1 + temp->index;
		return ;
	}
	*lst = new_cmd;
	new_cmd->index = 0;
}

void	ft_clearcmdlst(t_cmd **lst)
{
	t_cmd	*temp;
	t_data	*data;

	data = get_data();
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
		if ((*lst)->cmd) 
			gc_free_one(data->memblock, (*lst)->cmd);
		if ((*lst)->infile)
			gc_free_one(data->memblock, (*lst)->infile);
		if ((*lst)->outfile)
			gc_free_one(data->memblock, (*lst)->outfile);
		if ((*lst)->doc)
			ft_cleardoclst(&(*lst)->doc);
		gc_free_one(data->memblock, lst);
		*lst = temp;
			/*temp = (*lst)->next;
			if(*lst)
				gc_free_one(data->memblock, *lst);
			*lst = temp;*/
		}
	}
	lst = NULL;
	data->cmd = NULL;
}
