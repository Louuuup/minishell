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
	char 			*string;
	static int		i;

	i = 0;
	set_mode(pntr, MULTILINE);
	while (TRUE)
	{
		string = readline("> ");
		if (global_signal == 1)
			return (free(string), 1);
		if (string == NULL)
			break ;
		if (ft_strcmp(string, delimiter) == 0)
			break ;
		string = function_use_local_token(pntr, string);
		if (!string)
			return (close(fd), 2);
		ft_putendl_fd(string, fd);
		free(string);
		i++;
	}
	set_mode(pntr, NON_INTERACT);
	if (string != NULL)
		free(string);
	return (0);
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
	status = input_to_file_descriptor(pntr, file_descriptor, tab_cmd->redirections[i].value);
	if (status == 1 || status == 2)
		return (unlink(object), free(object), 1);
	close(file_descriptor);
	if (tab_cmd->redirections[i].no_space != 3)
		unlink(object);
	else
	{
		tab_cmd->file_in = open(object, O_RDONLY);
		if (tab_cmd->file_in == -1)
			return (free(object), error_out(pntr, 1));
		tab_cmd->last_multiline = ft_strdup(object);
	}
	free(object);
	return (0);
}