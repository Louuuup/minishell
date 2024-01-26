#include "minishell.h"

//singleton :)
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}
