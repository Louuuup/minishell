// #include "minishell.h"

// void	tmp_parse(t_data *data);

// void	prompt_create(t_data *data)
// {
// 	data->user_prompt = NULL;
// 	while (TRUE)
// 	{
// 		data->user_prompt = readline(PROMPT_NAME);
// 		if (data->user_prompt && !strncmp(data->user_prompt, "\0", 2))
// 		{
// 			free(data->user_prompt);
// 			data->user_prompt = NULL;
// 		}
// 		else
// 		{
// 			add_history(data->user_prompt);
// 			if (parser(data) == NO_ERROR && tokener(data) == NO_ERROR)
// 				exec_main(data);
// 		}
// 	}
// }

// // for me, will delete once we have the real parsing
// void	tmp_parse(t_data *data)
// {
// 	if (!ft_strncmp(data->user_prompt, "echo 1", 6))
// 	{
// 		char *str[] = {"echo", "-nnnnn", "coucou", "allo", "sheesh", "aaaa"};
// 		built_echo(str, 6, STDOUT_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "echo 2", 6))
// 	{
// 		char *str[] = {"echo", "-nnnann", "coucou", "allo", "sheesh", "aaaa"};
// 		built_echo(str, 6, STDOUT_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "pwd", 3))
// 		build_pwd(STDERR_FILENO);
// 	else if (!ft_strncmp(data->user_prompt, "cd src", 6))
// 	{
// 		char *str[] = {"cd", "src"};
// 		built_cd(str, 2, STDERR_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "cd ..", 5))
// 	{
// 		char *str[] = {"cd", ".."};
// 		built_cd(str, 2, STDERR_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "cd path", 7))
// 	{
// 		char *str[] = {"cd", "/Users/ycyr-roy/Desktop/REPO/minishell"};
// 		built_cd(str, 2, STDERR_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "cd REPO", 7))
// 	{
// 		char *str[] = {"cd", "REPO"};
// 		built_cd(str, 2, STDERR_FILENO);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "env", 7))
// 		built_env(data, 1);
// 	else if (!ft_strncmp(data->user_prompt, "export", 7))
// 	{
// 		char *str[] = {"export", NULL};
// 		built_export(str, 1, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "export ad=wasd", 14))
// 	{
// 		char *str[] = {"export", "ad=wasd"};
// 		built_export(str, 2, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "export ad=aa", 14))
// 	{
// 		char *str[] = {"export", "ad=aa"};
// 		built_export(str, 2, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "export a b c", 12))
// 	{
// 		char *str[] = {"export", "a", "b", "c"};
// 		built_export(str, 4, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "export b=", 9))
// 	{
// 		char *str[] = {"export", "b="};
// 		built_export(str, 2, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "export ALLO=", 9))
// 	{
// 		char *str[] = {"export", "ALLO="};
// 		built_export(str, 2, 1);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "exit", 4))
// 		built_exit();
// 	else if (!ft_strncmp(data->user_prompt, "unset b", 7))
// 	{
// 		char *str[] = {"unset", "b"};
// 		built_unset(str, 2, data);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "unset ad", 8))
// 	{
// 		char *str[] = {"unset", "ad"};
// 		built_unset(str, 2, data);
// 	}
// 	else if (!ft_strncmp(data->user_prompt, "unset", 5))
// 	{
// 		char *str[] = {"unset"};
// 		built_unset(str, 1, data);
// 	}
// }
