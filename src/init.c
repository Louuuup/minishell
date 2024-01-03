#include "../include/minishell.h"

//is responsible for duplicating the standard input (stdin) and standard output (stdout) file descriptors and storing the duplicated descriptors in a t_data structure

void	init_start_file_desc(t_data *pntr)
{
	pntr->first_stdout = dup(STDOUT_FILENO);
	if (pntr->first_stdout == -1)
		fd_exit(pntr, 1);
	pntr->first_stdin = dup(STDIN_FILENO);
	if (pntr->first_stdin == -1)
		fd_exit(pntr, 1);
}

//initiates the variables to defaults

void    init_pntr(t_data *pntr, char **env)
{
	pntr->mode = INTERACT;
	pntr->code_exit = 0;
	pntr->tokens = NULL;
	pntr->cmdt_count = 0;
	pntr->path = NULL;
	pntr->cmdt = NULL;
	pntr->input = NULL;
	pntr->max_token = 1;
	pntr->env = NULL;
	pntr->count_token = 0;
	init_start_file_desc(pntr);
}
