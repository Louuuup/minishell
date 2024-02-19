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

void ft_clearcmdlst(t_cmd **lst)
{
	t_cmd	*temp;
	t_data	*data;

	data = get_data();
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			gc_free_one(data->memblock, *lst);
			*lst = temp;
		}
	}
	lst = NULL;
}
