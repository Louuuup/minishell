#include "minishell.h"

t_doc	*ft_lstnewdoc(char *str)
{
	t_doc	*elm;

	elm = ft_calloc(1, sizeof(t_doc));
	if (!elm)
		return (NULL);
	elm->eof = str;
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

void ft_cleardoclst(t_doc **lst)
{

	t_doc	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			free (*lst);
			*lst = temp;
		}
	}
	lst = NULL;
}
