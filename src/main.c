#include "minishell.h"

//singleton :)
t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	data = get_data();
	bonjour(envp[0]);
	allo();
	return 0;
}
