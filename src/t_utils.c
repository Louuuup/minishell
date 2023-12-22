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
static void	*t_free(t_cmd *ptr)
{
	t_cmd *tmp;

	while(ptr)
	{
		tmp = ptr;
		if (tmp->cmd_path)
			tmp->cmd_path = free_null(tmp->cmd_path);
		if (tmp->args)
			tmp->args = arr_free((void **)tmp->args);
		ptr = ptr->next;
		free(tmp);
	}
	return (NULL);
}

void	free_all(t_data *data)
{
	if (data->env)
		data->env = arr_free((void **)data->env);
	if (data->cmd)
		data->cmd = t_free(data->cmd);
	// PLEASE ADD OTHER POINTERS TO FREE
}
