#include "minishell.h"

t_doc	*ft_lstnewdoc(char *str)
{
	t_doc	*elm;

	elm = gc_calloc(1, sizeof(t_doc));
	if (!elm)
		return (NULL);
	elm->eof = gc_strdup(str);
	elm->next = NULL;
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


void	ft_docadd_back(t_doc **lst, t_doc *new_cmd, int qts)
{
	t_doc	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp = ft_doclast(*lst);
		temp->next = new_cmd;
		temp->next->index = 1 + temp->index;
		if(qts)
			temp->expand = true;
		return ;
	}
	*lst = new_cmd;
	new_cmd->index = 0;
}

void ft_cleardoclst(t_doc **lst)
{
	t_doc	*temp;
	t_data	*data;

	data = get_data();
	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			gc_free_one(data->memblock, *lst);
			gc_free_one(data->memblock, (*lst)->eof);
			*lst = temp;
		}
	}
	lst = NULL;
}
