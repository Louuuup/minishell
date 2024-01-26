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

	data = get_data();
	ptr = calloc(count, size);
	if (!ptr)
		shell_error();
	data->memblock = memblock_add(data->memblock, ptr);
	return (ptr);
}

t_memblock	*memblock_add(t_memblock *memblock, void *ptr)
{
	t_memblock *new;

	new = gc_malloc(sizeof(t_memblock));
	new->ptr = ptr;
	new->next = memblock;
	return (new);
}

void	gc_free(t_memblock *memblock)
{
	t_memblock *tmp;

	while (memblock)
	{
		tmp = memblock->next;
		free(memblock->ptr);
		free(memblock);
		memblock = tmp;
	}
}
