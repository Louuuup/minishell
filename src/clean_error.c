#include "minishell.h"

void	clean_err(t_data *data, t_cmd *cmd)
{
	ft_free_err(data);
	close_fds(cmd);
}

int	ft_free_err(t_data *data)
{
	if (data->parser.cmd_list)
		gc_free_one(data->memblock, data->parser.cmd_list);
	if (data->parser.free != NULL)
		ft_free3darray(data->parser.free);
	ft_clear_lst_err(&data->cmd);
	return (1);
}

void	ft_clear_lst_err(t_cmd **lst)
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
			/*if ((*lst)->infile)
				gc_free_one(data->memblock, (*lst)->infile);
			if ((*lst)->outfile)
				gc_free_one(data->memblock, (*lst)->outfile);*/
			if ((*lst)->doc)
				ft_cleardoclst(&(*lst)->doc);
			gc_free_one(data->memblock, lst);
			*lst = temp;
		}
	}
	//lst = NULL;
	//data->cmd = NULL;
}
