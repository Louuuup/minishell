#include "../include/minishell.h"

//the function free the memory allocated for a dynamic array of strings (char **p)

void	free_string_array(char **pnt)
{
	int	i;
	i = 0;
	if (pnt)
	{
		
		while (pnt[i])
		{
			free(pnt[i]);
			pnt[i++] = NULL;
		}

		free(pnt);
		pnt = NULL;
	}
}