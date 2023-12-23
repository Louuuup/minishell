#include "minishell.h"

//it creates a temp filename for a heredoc file

char	name_create_multiline(int i)
{
	char	*with_itoa;
	char	*file_name;

	with_itoa = ft_itoa(i);
	if (!with_itoa)
		return (NULL);
	file_name = ft_strcat(".tmp_hdoc", with_itoa);
	free(with_itoa);
	return (file_name);
}

//it reads user input, stops on the delimiter, writes to a file descriptor

int	input_to_file_descriptor(t_data *pntr, int fd, char *delimiter)
{
	static int		j;
	char 	*line;

	j = 0;
	
}

//it makes a temp file, puts the heredoc into it,
//then unlinks the file or sets it as the input

int	create_heredoc(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	char	*object;
	int		status;
	int		file_descriptor;

	object = name_create_multiline(i);
	if (!object)
		return (error_out(pntr, 1), 1);
	file_descriptor = open(object, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (file_descriptor < 0)
		return (free(object), error_out(pntr, 1));
	status = 1;
	
	return (0);
}