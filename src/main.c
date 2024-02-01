#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	data = get_data();
	(void)argv; //not needed
	(void)argc; //not needed
	init_all(data, envp); //initialises all data
	while (TRUE) //main loop
	{
		data->user_prompt = readline(PROMPT_NAME);
		if (data->user_prompt && !ft_strncmp(data->user_prompt, "\0", 2)) //if user input is empty
		{
			free(data->user_prompt);
			data->user_prompt = NULL;
		}


		else //if user input is not empty
		{
			add_history(data->user_prompt);
			if (parser(data) == NO_ERROR && tokener(data) == NO_ERROR) //can remove one of the two if called elsewhere
				exec_main(data); //not implemented yet
		}
	}

	return (NO_ERROR);
}
