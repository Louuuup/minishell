#include "minishell.h"

int	tok_app(char *str, t_idtok *id, t_cmd *tmp)
{
	t_data *data;
	int		fd;

	data = get_data();
	if (tmp->outfile)
	{
		fd = open(tmp->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		close(fd);
		if ((access(tmp->outfile, W_OK)) == -1)
		{
			error_str_file("permission denied: ", tmp->outfile);
			return (0);
		}
	}
	ft_expansion(str, &tmp->outfile);
	ft_removeqte(tmp->outfile);
	tmp->out_flag = REDIR_APPEND;
	id->app = false;
	return (1);
}

int	tok_in(char *str, t_idtok *id, t_cmd *tmp)
{
	t_data *data;

	data = get_data();
	if (tmp->infile)
	{
		if (access(tmp->infile, R_OK) == -1)
		{
			error_str_file("permission denied: ", tmp->infile);
			return (0);
		}
	}
	ft_expansion(str, &tmp->infile);
	ft_removeqte(tmp->infile);
	tmp->in_flag = REDIR_INPUT;
	id->in = false;
	return (1);
}

int	tok_out(char *str, t_idtok *id, t_cmd *tmp)
{
	int		fd;
	t_data	*data;

	data = get_data();
	if (tmp->outfile)
	{
		fd = open(tmp->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fd);
		if ((access(tmp->outfile, W_OK)) == -1)
		{
			error_str_file("permission denied: ", tmp->outfile);
			return (0);
		}
	}
	ft_expansion(str, &tmp->outfile);
	ft_removeqte(tmp->outfile);
	tmp->out_flag = REDIR_OVERWRITE;
	id->out = false;
	return (1);
}

int	tok_cmd(char *str, t_idtok *id, t_cmd *tmp)
{
	if (is_directory(str))
	{
		error_str_file("this is a directory : ", str);
		get_data()->code_exit = 126;
		return (0);
	}
	tmp->cmd = gc_malloc((id->cmd_size + 1) * (sizeof(char *)));
	ft_expansion(str, &tmp->cmd[0]);
	ft_removeqte(tmp->cmd[0]);
	id->cmd = true;
	ft_builtincheck(tmp);
	tmp->cmd[1] = NULL;
	return (1);
}

int	ft_id_cmd_file_arg(char *str, t_idtok *id, t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	if (id->app)
		return (tok_app(str, id, tmp));
	else if (id->in)
		return (tok_in(str, id, tmp));
	else if (id->out)
		return (tok_out(str, id, tmp));
	else if (id->here)
		return (tok_doc(str, id, tmp));
	else if (!id->cmd)
		return (tok_cmd(str, id, tmp));
	else if (id->cmd)
		return (tok_arg(str, tmp));
	return (1);
}
