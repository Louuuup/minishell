#include "../include/minishell.h"

int ft_heredoc(t_cmd *cmd)
{
	int fd;

	fd = ft_makedoc(cmd);
	ft_editdoc(fd ,cmd);
	return(0);
}

int ft_editdoc(int fd, t_cmd *cmd)
{
	char 		*tmp;
	struct stat init;
	struct stat mod;
	mode_t 		mode;
	int 		f;
	
	if(cmd)
		tmp = NULL;
	f = stat("heredoc", &init);
	mode = init.st_mode;
	tmp = readline("heredoc >");
	while(f == 0)
	{
		f = stat("heredoc", &mod);
		if(f != 0 || mode != mod.st_mode)
		{
			ft_putstr_fd("File was tempered\n", 2);
			break;
		}
		
	}
	if(ft_strncmp("stop", tmp, 5) != 0)
	{
		free(tmp);
		return(SUCESS);
	}
	ft_putendl_fd(tmp, fd);
	free(tmp);
	return (SUCESS);
}

int ft_makedoc(t_cmd *cmd)
{
	int fd;
	static int i;

	if(cmd)
		i = 1;
	fd = open("heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		ft_putstr_fd("cant make file", 2);
	return(fd);
}