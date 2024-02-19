#include "minishell.h"

void *ft_free3darray(char ***array)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data();
	if (!array)
		return (NULL);
	while (array[i])
	{
		printf("%s\n", array[i][0]);
		ft_free_2darray(array[i]);
		i++;
	}
	printf("WHAT\n");
	if (array)
		gc_free_one(data->memblock, array);
	printf("FUCK\n");
	return (NULL);
}

void	*ft_free_2darray(char **array)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data();
	if (!array)
		return (NULL);
	while (array[i])
	{
		gc_free_one(data->memblock, array[i]);
		i++;
	}
	printf("2d\n");
	if(array)
		gc_free_one(data->memblock, array);
	return (NULL);
}

int ft_freeparse(t_data *data)
{	
	if(data->parser.cmd_list)
    	gc_free_one(data->memblock ,data->parser.cmd_list);
	if(data->parser.free)
		//ft_free3darray(data->parser.free);
	ft_clearcmdlst(&data->cmd);
    return(1);
}