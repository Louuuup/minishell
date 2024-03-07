#include "minishell.h"

void heredoc_loop(t_doc *doc)
{
	char *tmp;
	char *line;

	while (true)
	{
	line = readline("> ");
		if (!line)
	break;
	if (ft_strcmp(line, doc->eof) == 0)
	{
		free(line);
		break;
	}
	if (doc->expand == true)
	{	
		ft_doc_exp(line, &tmp);
		heredoc_addline(doc, tmp);
	}
	else
	heredoc_addline(doc, line);
	free(line);
	}}


int heredoc_newfile(t_doc *doc)
{
	t_data *data;
	char *tmp;

	data = get_data();
	tmp = ft_itoa(data->hd_count);
	data->hd_count++;
	doc->name = gc_strjoin("/tmp/heredoc_", tmp);
	free(tmp);
	doc->fd = open(doc->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc->fd == -1)
		return (shell_error());
	//data->docfd = &doc->fd;
	return (NO_ERROR);
}

int heredoc_addline(t_doc *doc, char *line)
{
	if (!write(doc->fd, line, ft_strlen(line)))
		return (ERROR);
	if (!write(doc->fd, "\n", 1))
		return (ERROR);
	return (NO_ERROR);
}

int heredoc_create(t_cmd *cmd)
{
	pid_t 	pid;
	t_doc 	*doc;
	int		status;

	status = 0;
	doc = cmd->doc;
	pid = fork();
	if (pid < 0)
		error_str("fork error\n");
	if (pid == 0)
	{
	signal(SIGINT, sigcdocint);
	while(doc)
	{
		heredoc_newfile(doc);
		heredoc_loop(doc);
    	close(doc->fd);
		doc = doc->next;
	}
	}
	if (pid != 0)
		waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)){
		dprintf(2 ,"FUCK\n");
		return (ERROR);}
	return (NO_ERROR);
}

int heredoc_use(t_cmd *cmd)
{
    t_doc *doc;
    doc = cmd->doc;

    while (doc)
    {
        if (doc->next)
            doc = doc->next;
        else
            break;
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
