#include "minishell.h"

//cleans memory taken by pntr->cmdt

void	cmdt_cleaning(t_data *pntr)
{

}

//the function is responsible for freeing memory allocated for various components of the t_data structure

void	pntr_cleaning(t_data *pntr)
{
	int	i;

	i = 0;
	if (pntr->tokens)
	{
		while (0 < pntr->count_token)
			free(pntr->tokens[--pntr->count_token].value);
		free(pntr->tokens);
		pntr->tokens = NULL;
	}
	cmdt_cleaning(pntr);
	if (pntr->input)
	{
		free(pntr->input);
		pntr->input = NULL;
	}
	if (pntr->path)
	{
		while (pntr->path[i])
		{
			free(pntr->path[i]);
			i++;
		}
		free(pntr->path);
		pntr->path = NULL;
	}
}

//function for safely freeing the memory associated with an array of strings

void	double_pntr_cleaning(char **pntr)
{
	if (!pntr)
		return;

	while (*pntr)
	{
		free(*pntr);
		*pntr++ = NULL;
	}

	free(pntr);
	pntr = NULL;
}

//the function is responsible for cleaning up file descriptors and resources associated with output redirection and here documents

void	fd_cleaning(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	if (tab_cmd->out_fd	!= -1)
		close(tab_cmd->out_fd);
	else if (tab_cmd->in_fd != -1)
		close(tab_cmd->in_fd);
	if (pntr->cmdt[i].last_multiline)
	{
		unlink(pntr->cmdt[i].last_multiline);
		free(pntr->cmdt[i].last_multiline);
	}
}

//the function designed to release resources and perform cleanup tasks before the program exits. It frees memory, closes file descriptors, and delegates additional cleanup to the clean_stuff function.

void	total_clean(t_data *pntr)
{
	double_pntr_cleaning(pntr->env);

	close(pntr->first_stdin);
	close(pntr->first_stdout);
}