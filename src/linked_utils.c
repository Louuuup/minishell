#include "minishell.h"

t_cmd	*ft_lstnewcmd(void)
{
	t_cmd	*elm;

	elm = gc_calloc(1, sizeof(t_cmd));
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


void	ft_cmdadd_back(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp = ft_cmdlast(*lst);
		temp->next = new_cmd;
		temp->next->index = temp->index++;
		return ;
	}
	*lst = new_cmd;
	new_cmd->index = 0;
}
