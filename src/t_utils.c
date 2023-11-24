#include "minishell.h"

t_cmd	*add_cmd(t_cmd *cmd)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		ft_error(ERR_ALLOC);
	cmd->next = new;

	return (new);
}
