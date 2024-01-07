#include "minishell.h"

//The function handles cases where the PATH environment variable is not set and checks for the existence of the command in the current directory, updating the command and handling errors accordingly

int	is_command(t_data *pntr, t_tab_cmd *tab_cmd)
{
	char	*result;
	char	*temporary;

	if (pntr->path != NULL)
		return (1);
	temporary = ft_strdup("./");
	if (!temporary)
		return(error_out(pntr, "ft_strdup", 1) + 1);
	result = ft_strjoin(temporary, tab_cmd->cmd);
	if (!result)
		return (error_out(pntr, "ft_strjoin", 1) + 1);
	if (access(result, 0) == 0)
	{
		temporary = tab_cmd->cmd;
		tab_cmd->cmd = result;
		free(temporary);
				ft_printf_fd(2, "minishell: %s: Permission denied\n", tab_cmd->cmd);
		pntr->code_exit = 126;
		return (0);
	}
	free(result);
	return (1);
}

//function checks if a specified command or file path is valid for execution. It checks whether the file exists, whether it is a directory, and whether it is executable. It prints appropriate error messages and sets the exit code accordingly. The function returns 0 for success and 1 for failure.

int check_valid_execution(t_tab_cmd *tab_cmd, t_data *pntr)
{
	DIR *directory;

	if (access(tab_cmd->cmd, 0) == 0)
	{
		directory = opendir(tab_cmd->cmd);
		if (directory)
		{
			ft_printf_fd(2, "minishell: %s: Is a directory\n", tab_cmd->cmd);
			pntr->code_exit = 126;
			closedir(directory);
		}
		else if (access(tab_cmd->cmd, X_OK) == 0)
			return (0);
		else
		{
			ft_printf_fd(2, "minishell: %s: No permission\n",
				tab_cmd->cmd);
			pntr->code_exit = 126;
		}
		return (1);
	}
	ft_printf_fd(2, "minishell: %s: No such file or directory\n",
		tab_cmd->cmd);
	pntr->code_exit = 127;
	return (1);
}

//"search_in_path", is responsible for searching the provided command in the directories specified in the PATH environment variable. It iterates through each directory in the PATH, concatenates the directory path with the command, and checks if the resulting path is executable. If an executable path is found, it updates the "cmd_table->cmd" field with the full path to the executable.

int	path_searching(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	char	*result;
	char	*temporary;

	while (pntr->path[++i] && pntr->path)
	{
		if (tab_cmd->cmd[0] == '\0')
			break ;
		temporary = ft_strdup(pntr->path[i]);
		if (!temporary)
			return (error_out(pntr, "ft_strdup", 1) + 1);
		temporary = ft_strjoin(temporary, "/");
		if (!temporary)
			return (error_out(pntr, "ft_strjoin", 1) + 1);
		result = ft_strjoin(temporary, tab_cmd->cmd);
		if (!result)
			return (error_out(pntr, "ft_strjoin", 1) + 1);
		if (access(result, X_OK) == 0)
		{
			temporary = tab_cmd->cmd;
			tab_cmd->cmd = result;
			return (free(temporary), 0);
		}
		free(result);
	}
	return (find_path(pntr, tab_cmd));
}

//'search_if_exist' is responsible for checking if a given command exists in the directories listed in the PATH environment variable

int	is_exist(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	char	*result;
	char	*temporary;

	while (pntr->path && pntr->path[++i])
	{
		temporary = ft_strdup(pntr->path[i]);
		if (!temporary)
			return (error_out(pntr, "ft_strdup", 1) + 1);
		result = ft_strjoin(temporary, tab_cmd->cmd);
		if (!result)
			return(error_out(pntr, "ft_strjoin", 1) + 1);
		if (access(result, 0) == 0)
		{
			temporary = tab_cmd->cmd;
			tab_cmd->cmd = result;
			free(temporary);
			ft_printf_fd(2, "minishell: %s: No permission\n",
				tab_cmd->cmd);
			pntr->code_exit = 126;
			return (0);
		}
		free(result);
	}
	return (is_command(pntr, tab_cmd));
}

//the function is responsible for locating an executable binary in the system
//and determining whether it is available for execution (127 - command not found)

int find_exec(t_data *pntr, t_tab_cmd *tab_cmd)
{
	int i;
	int result;

	i = -1;
	if (!tab_cmd->cmd)
		return (1);
	if (tab_cmd->cmd[0] == '\0')
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", tab_cmd->cmd);
		pntr->code_exit = 127;
		return (1);
	}
	if (tab_cmd->cmd[0] == '.' || ft_strchr(tab_cmd->cmd, '/') != 0)
		return (check_valid_execution(tab_cmd, pntr));
	result = path_searching(pntr, tab_cmd, i);
	if (result == 0)
		return (0);
	else if (result == 2)
		return (1);
	if (is_exist(pntr, tab_cmd, i) == 1)
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", tab_cmd->cmd);
		pntr->code_exit = 127;
	}
	return (1);
}