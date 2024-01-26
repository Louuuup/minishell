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
			pnt[i] = NULL;
			i++;
		}
		free(pnt);
		pnt = NULL;
	}
}

//function is used to exit the shell program with a specified exit code
void	fd_exit(t_data *pntr, int code_exit)
{
	if (code_exit == 1)
		perror("An error!");
	total_clean(pntr);
	exit(1);
}

int	ft_putstr_int(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		ft_putchar_fd(*s++, fd);
		i++;
	}
	return (i);
}