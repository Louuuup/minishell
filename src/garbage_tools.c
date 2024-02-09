#include "minishell.h"


void	*gc_malloc(size_t size)
{
	void	*ptr;
	t_data	*data;

	data = get_data();
	ptr = malloc(size);
	if (!ptr)
		shell_error();
	data->memblock = memblock_add(data->memblock, ptr);
	return (ptr);
}

void	*gc_calloc(size_t count, size_t size)
{
	void	*ptr;
	t_data	*data;

	if (DEBUG_ON)
		printf("(gc_calloc) Allocating %lu bytes\n", count * size);
	data = get_data();
	ptr = ft_calloc(count, size);
	if (!ptr)
		shell_error();
	data->memblock = memblock_add(data->memblock, ptr);
	return (ptr);
}

char *gc_strjoin(char *s1, char *s2)
{
    char *new_str;
    t_data *data;
    int len[2];

    if (s1 == NULL || s2 == NULL)
        return (NULL);
    data = get_data();
    len[0] = ft_strlen(s1);
    len[1] = ft_strlen(s2);
    new_str = gc_calloc(len[0] + len[1] + 1, sizeof(char));
    data->memblock = memblock_add(data->memblock, new_str);
    ft_strlcpy(new_str, s1, len[0] + 1);
    ft_strlcpy(new_str + len[0], s2, len[1] + 1);
    return (new_str);
}
