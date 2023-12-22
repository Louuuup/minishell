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

//it makes a temp file, puts the heredoc into it,
//then unlinks the file or sets it as the input

int	create_heredoc(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	char	*object;
	int		status;
	int		file_descriptor;

	object = 0;
}