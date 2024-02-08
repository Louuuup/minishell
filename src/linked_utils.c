#include "minishell.h"

t_cmd	*ft_lstnewcmd(void);
{
	t_cmd	*elm;

	elm = ft_calloc(sizeof(t_cmd));  //change to gc_calloc
	if (!elm)
		return (NULL);
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


void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp = ft_cmdlast(*lst);
		temp->next = new;
		temp->next->index = temp->index++;
		return ;
	}
	*lst = new;
	new->index = 0;
}
