/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:41:37 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 14:41:37 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mode_check(t_doc *doc, char *line)
{
	if (!line)
	{
		close(doc->fd);
		return (NO_ERROR);
	}
	if (ft_strcmp(line, doc->eof) == 0)
	{
		free(line);
		close(doc->fd);
		return (NO_ERROR);
	}
	if (doc->f == 0)
	{
		doc->f = stat(doc->name, &doc->inloopmod);
		if (doc->f != 0 || doc->mode != doc->inloopmod.st_mode)
		{
			error_str_file("File was tempered : ", doc->name);
			return (ERROR);
		}
	}
	return (1);
}

int	child_routine(t_doc *doc)
{
	char	*tmp;
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (!ft_mode_check(doc, line))
			return (NO_ERROR);
		else if (ft_mode_check(doc, line) < 0)
			return (ERROR);
		else if (doc->expand == true)
		{
			ft_doc_exp(line, &tmp);
			heredoc_addline(doc, tmp);
		}
		else
			heredoc_addline(doc, line);
		free(line);
	}
}

int	parent_routine(pid_t pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		exit_code(128 + (WTERMSIG(status)));
		return (ERROR);
	}
	if (WIFEXITED(status))
		return (NO_ERROR);
	return (ERROR);
}

void	cleanupdoc(t_data *data, t_cmd *cmd)
{
	if (cmd)
	{
		if (data->parser.cmd_list)
			gc_free_one(data->memblock, data->parser.cmd_list);
		if (data->parser.free != NULL)
			ft_free3darray(data->parser.free);
		clean_heredocs_files(cmd);
		ft_clearcmddoc(&data->cmd);
	}
}

void	ft_clearcmddoc(t_cmd **lst)
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
			if ((*lst)->infile)
				gc_free_one(data->memblock, (*lst)->infile);
			if ((*lst)->outfile)
				gc_free_one(data->memblock, (*lst)->outfile);
			if ((*lst)->doc)
				ft_cleardoctrlc(&(*lst)->doc);
			gc_free_one(data->memblock, lst);
			*lst = temp;
		}
	}
	lst = NULL;
	data->cmd = NULL;
}
