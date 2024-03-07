#include "minishell.h"

int	syntax_check(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if((!ft_strcmp(str[i], "<<") || !ft_strcmp(str[i], "<") ||\
			!ft_strcmp(str[i], ">") || !ft_strcmp(str[i], ">>"))\
				&& !str[i + 1])
				{
					exit_code(1);
					error_str_file("syntax error with token ", str[i]);
					return (0);
				}
		i++;
	}
	return (1);
}

int	id_tok(char *str, t_idtok *id, t_data *data)
{
	if (!ft_strcmp(str, "<<"))
		return (ft_idheredoc(id));
	else if (!ft_strcmp(str, "<"))
		return (ft_idinput(id));
	else if (!ft_strcmp(str, ">>"))
		return (ft_idappend(id));
	else if (!ft_strcmp(str, ">"))
		return (ft_idoutput(id));
	else
		return (ft_id_cmd_file_arg(str, id, data));
	return (0);
}

int	parsing(char **str, t_data *data)
{
	t_idtok	id;

	id.app = false;
	id.cmd = false;
	id.out = false;
	id.here = false;
	id.in = false;
	id.i = 0;
	id.cmd_size = 0;
	while (str[id.i])
	{
		id.cmd_size++;
		id.i++;
	}
	if(!syntax_check(str))
		return (0);
	id.i = 0;
	while (str[id.i])
	{                                     
		if (!id_tok(str[id.i], &id, data))
			return (0);                 	//add error code here
		id.i++;
	}
	return (1);
}

int	tokenizer(t_data *data)
{
	int	i;

	i = 0;
	while (data->parser.cmd_list[i])
	{
		ft_cmdadd_back(&data->cmd, ft_lstnewcmd());
		data->parser.free[i] = ft_split_tok(data->parser.cmd_list[i]);
		data->parser.free[i + 1] = NULL;
		if (!parsing(data->parser.free[i], data))
			return (0);
		i++;
	}
	data->parser.free[i] = NULL;
	return (1);
}
