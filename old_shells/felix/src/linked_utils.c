#include "../include/minishell.h"

t_cmd	*ft_lstnewcmd(char *cmd)
{
	t_cmd	*elm;

	elm = malloc(sizeof(t_cmd));
	if (!elm)
		return (NULL);
	elm->cmd = ft_split(cmd, ' ');
	elm->token = NULL;
	ft_builtincheck(elm);
	elm->next = NULL;
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
		return ;
	}
	*lst = new;
}
