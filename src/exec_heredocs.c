#include "minishell.h"

int heredoc_newfile(t_doc *doc)
{
	t_data *data;
	char *tmp;

	data = get_data();
	tmp = ft_itoa(data->hd_count);
	data->hd_count++;
	doc->name = ft_strjoin("/tmp/heredoc_", tmp);
	free(tmp);
	doc->fd = open(doc->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (doc->fd == -1)
		return (shell_error());
	return (NO_ERROR);
}

int heredoc_addline(t_doc *doc, char *line)
{
	write(doc->fd, line, ft_strlen(line));
	write(doc->fd, "\n", 1);
	return (NO_ERROR);
}

int heredoc_create(t_cmd *cmd)
{
	char *line;
	t_doc *doc;

	doc = cmd->doc;
	while(doc)
	{
		heredoc_newfile(doc);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, doc->eof) == 0)
			{
				free(line);
				break;
			}
			heredoc_addline(doc, line); // WIP
			// heredoc_addline(doc, ft_expansion(line, doc->expand)); // WIP
			free(line);
		}
        close(doc->fd);
		doc = doc->next;
	}
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