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

t_memblock *memblock_create(void *ptr)
{
	t_memblock *memblock;

	memblock = ft_calloc(1, sizeof(t_memblock));
	if (!memblock)
	{
		error_str("malloc error\n");
		return (NULL);
	}
	memblock->ptr = ptr;
	memblock->next = NULL;
	return (memblock);
}

t_memblock	*memblock_add(t_memblock *memblock, void *ptr)
{
	t_memblock *new;

	if (!memblock)
	{
		if (DEBUG_ON)
			printf("memblock is NULL\n");
		return (memblock_create(ptr));
	}
	new = ft_calloc(1, sizeof(t_memblock));
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
