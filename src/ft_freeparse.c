#include "minishell.h"

void	*ft_free_2darray(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int ft_freeparse(t_data *data)
{
    free(data->parser.cmd_list);
    ft_free_2darray(data->parser.sgl_cmd);
    ft_clearcmdlst(&data->cmd);
    return(1);
}