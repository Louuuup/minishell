#include "minishell.h"

//function checks if a specified command or file path is valid for execution. It checks whether the file exists, whether it is a directory, and whether it is executable. It prints appropriate error messages and sets the exit code accordingly. The function returns 0 for success and 1 for failure.

int check_valid_execution(t_tab_cmd *tab_cmd, t_data *pntr)
{
	DIR *directory;

	if (access(tab_cmd->cmd, 0) == 0)
	{
		directory = opendir(tab_cmd->cmd);
		if (directory)
		{
			pntr->code_exit = 126;
			ft_putstr_fd("minishell: that's a directory", 2);
			closedir(directory);
		}
		else if (access(tab_cmd->cmd, X_OK) == 0)
			return (0);
		else
		{
			pntr->code_exit = 126;
			ft_putstr_fd("minishell: No permission\n", 2);
		}
		return (1);
	}
	pntr->code_exit = 127;
	ft_putstr_fd("minishell: No file / directory\n", 2);
	return (1);
}

//is responsible for locating an executable binary in the system
//and determining whether it is available for execution (127 - command not found)

int find_exec(t_data *pntr, t_tab_cmd *cmd_tab)
{
	int i;
	int result;

	i = -1;
	if (!cmd_tab->cmd)
		return (1);
	if (cmd_tab->cmd[0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		pntr->code_exit = 127;
		return (1);
	}
	if (cmd_tab->cmd[0] == '.' || ft_strchr(cmd_tab->cmd, '/') != 0)
		return (check_valid_execution(cmd_tab, pntr));
	
	return (1);
}