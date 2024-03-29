/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:39 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/11 14:25:39 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_loop(t_doc *doc)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_str("fork error\n");
	if (pid == 0)
	{
		signal(SIGINT, sigcdocint);
		if (child_routine(doc) == ERROR)
			sigcdocint(SIGINT);
		gc_free_all(get_data()->memblock);
		exit(0);
	}
	else if (pid > 0)
		return (parent_routine(pid));
	return (NO_ERROR);
}

int	heredoc_newfile(t_doc *doc)
{
	t_data	*data;
	char	*tmp;

	data = get_data();
	tmp = ft_itoa(data->hd_count);
	data->hd_count++;
	doc->name = gc_strjoin("/tmp/heredoc_", tmp);
	free(tmp);
	doc->fd = open(doc->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (doc->fd == -1)
		return (shell_error());
	data->docfd = &doc->fd;
	return (NO_ERROR);
}

int	heredoc_addline(t_doc *doc, char *line)
{
	if (!write(doc->fd, line, ft_strlen(line)))
		return (ERROR);
	if (!write(doc->fd, "\n", 1))
		return (ERROR);
	return (NO_ERROR);
}

int	heredoc_create(t_cmd *cmd)
{
	t_doc	*doc;

	doc = cmd->doc;
	while (doc)
	{
		heredoc_newfile(doc);
		doc->f = stat(doc->name, &doc->init);
		doc->mode = doc->init.st_mode;
		if (heredoc_loop(doc) == ERROR)
		{
			close(doc->fd);
			return (ERROR);
		}
		close(doc->fd);
		doc = doc->next;
	}
	return (NO_ERROR);
}

int	heredoc_use(int fd, t_cmd *cmd)
{
	t_doc	*doc;

	if (fd > 2)
		close(fd);
	doc = cmd->doc;
	while (doc)
	{
		if (doc->next)
			doc = doc->next;
		else
			break ;
	}
	doc->fd = open(doc->name, O_RDONLY);
	if (doc->fd == -1)
		return (shell_error());
	if (access(doc->name, F_OK) != -1 && DEBUG_ON)
		printf("(heredoc_use) file '%s' exists!\n", doc->name);
	else if (DEBUG_ON)
		printf("(heredoc_use) file '%s' does not exist!\n", doc->name);
	return (doc->fd);
}
