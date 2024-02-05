#include "minishell.h"


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
