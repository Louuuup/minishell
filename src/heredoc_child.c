#include "minishell.h"


void child_routine(pid_t pid)
{
    t_data *data;
    t_cmd   *tmp;

    printf("Child: I'm the child, my internal pid is %d.\n", pid);
    data = get_data();
	tmp = data->cmd;
    signal(SIGINT, sigcdocint);
	while (tmp)
	{
		if (tmp->doc)
			(heredoc_create(tmp));
		tmp = tmp->next;
	}
	//kill(pid, SIGTERM);
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