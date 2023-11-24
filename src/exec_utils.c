#include "minishell.h"

void	ft_dup2(int fd, int std)
{
	int	err;

	err = dup2(fd, std);
	if (err == -1)
		ft_error(ERR_DUP);
	close(fd);
}
