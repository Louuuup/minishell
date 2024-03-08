#include "minishell.h"


void child_routine(t_doc *doc)
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
    close(doc->fd);
    }
}

int parent_routine(pid_t pid)
{
    int		status;

    waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)){
		return (ERROR);}
	printf("Parent: My child exited with status %d\n", status);
	if (WIFEXITED(status))
    {
        return(NO_ERROR);
        printf("Parent: Child [%d] terminated normally.\n", pid);
    }
    return (ERROR);
}