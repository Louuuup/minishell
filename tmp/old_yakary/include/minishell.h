#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
// # include <readline.h>
# include <readline/readline.h> //i don't know why but it works on my mac's account
// # include <history.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>

//==================VALUES===================//
# define DEBUG_ON 0
# define TRUE 1
# define FALSE 0
# define YES 1
# define NO 0
# define PROMPT_NAME "\033[35m\033[1mminiSHELL \033[0m\033[1m→ \033[0m"
# define EXPORT_PREFIX "declare -x "
//==================ERRORS===================//
# define ERR_MAIN "\033[31m\033[1mERROR > \033[0m"
# define ERR_EXP "\033[37m\033[1mREASON\033[0m"
# define ERR_FORK "Forked up!\n"
# define ERR_ALLOC "Allocation error\n"
# define ERR_PIPE "Couldn't open the pipe\n"
# define ERR_DUP "Dup error\n"
# define ERR_CD_ARGS "Too much arguments for CD\n"
# define ERR_CD "Invalid name or path\n"
# define ERR_EXPORT "Invalid identifier for export\n"
# define ERR_UNSET "Invalid indentifier for unset\n"
# define ERR_WRITE "Write error\n"
//==================Structs===================//

extern int	global_signal;

// /**
//  * NOTE: Simple command + args
// *@param	argc Number of args.
// *@param	argv Array of cmd + all its args.
// *@param	next Next command.
// */
// struct cmd;
typedef struct cmd
{
	int			argc;    // number of arguments (plus cmd)
	int			fd[2]; //fd[0] is in and fd[1] is out. FOR ME. if =0, std.
	int			cmd_idx; // starts at 0, index for commands, to keep up more easily.
	char		*cmd_path; //for me
	char		**args; //args[0] is cmd, and the others are the arguments.
	struct cmd	*next; //points to another struct like this one with the next command, or NULL if its the last command
}			t_cmd;

typedef	enum s_type_token
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_MULTILINE,
	DQUOTE,
	SQUOTE
}	t_type_token;

typedef	enum s_set_mode
{
	INTERACT,
	NON_INTERACT,
	CHILD,
	MULTILINE
}	t_set_mode;

typedef	struct s_token
{
	char			*value;
	t_type_token	type;
	int				no_space;
}	t_token;

typedef struct s_tab_cmd
{
	char	*cmd;
	char	**args;
	int		in_fd;
	int		out_fd;
	t_token	*redirections;
	int		file_in;
	int		file_out;
	int		num_redirections;
	int		num_args;
	int		is_child_process;
	char	*last_multiline;
	pid_t	pid;
}	t_tab_cmd;

typedef struct s_data
{
	t_cmd		*cmd; //pointer to first cmd, linked to the other ones with chained list. (YOU NEED TO ALLOCATE AND PARSE IN HERE)
	// int			cmd_count; //the amount of commands in the chained list.
	char		**env; //to free
	char		**path;
	char		*input;
	t_token		*tokens;
	int			count_token;
	int			max_token;
	t_tab_cmd	*cmdt;
	int			cmdt_count;
	char		*user_prompt; //to free
	int			code_exit;
	// int		exit_promt;
	int			fd_before;
	int			first_stdin;
	int			first_stdout;
	t_set_mode	mode;
}	t_data;


typedef	struct	s_redir
{
	int		i;
	char	*name;
	char	*value;
}	t_redir;

typedef struct	s_copy
{
		char	*wc;
		char	**args;
		char	*cmd;
		int		i;
		int		num;
		t_redir	redir;
}	t_copy;

/**
 * NOTE: Multiple cmds when pipe
*@param	infile path to infile
*@param	outfile path to outfile
*@param	first_cmd first cmd in chained lst.
*/
typedef struct cmd_table
{
	char	*infile;
	char	*outfile;
	t_cmd	*first_cmd;
}			t_table;

//
//==================[utils.c]===================//
t_data	*get_data(void);
void	ft_error(char *str);
void	my_error(char *str);
int 	error_out(t_data *pnt, char *s, int n);
void	safe_free(void **ptr);
void	error_in_syntax(int type, t_data *pntr);
//
//==================[t_utils.c]===================//
void	free_all(t_data *data);
//
//==================[prompt.c]===================//
void	prompt_create(t_data *data);
//
//==================[builtin.c]===================//
void	build_pwd(t_data *pnt);
int		if_builtin(t_tab_cmd *cmd_tab);
void    shoot_builtin(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd);
//
//==================[exec.c]===================//
void	exec_main(t_data *data);
void	alt_exec_main(t_data *pntr);
//
//==================[exec_utils.c]===================//
char	*ft_get_env(char *str, char **env);
char	*cmd_fullpath(t_data *data, char *cmd);
void	ft_dup2(int fd, int std);
void	ft_pipe(t_cmd *cmd);
int		change_fd_input_output(t_data *pntr, t_tab_cmd *tab_cmd, int *fd, int i);
int		find_path(t_data *pntr, t_tab_cmd *tab_cmd);
//
//==================[b_cd.c]===================//
void	built_cd(char **args, int argc);
//
//==================[b_exit.c]===================//
void	built_exit(t_data *pntr, t_tab_cmd *cmd_tab);
//
//==================[b_echo.c]===================//
void	built_echo(char **args, int argc, int fd_out);
//
//==================[b_unset.c]===================//
void	built_unset(char **args, int argc, t_data *data);
//
//==================[b_env.c]===================//
void	index_sort(char **arr, int str_count, int *index);
void	print_env(char **env, int fd);
void	built_env(t_data *data);
//
//==================[b_export.c]===================//
int		var_in_env(char *str);
void	print_export(char **env, int fd);
void	built_export(t_data *data, t_tab_cmd *cmd, int fd_out);
//
//==================[parser.c]===================//
int		parser(t_data *pointer);
//
//==================[parser_func.c]===================//
int 	redirections_fill(t_data *pointer, int i, int j);
int		args_cmd_fill(t_data *pnt, int j, int i, int k);
int		words_merging(t_data *pointer);
//
//==================[parser_utils.c]===================//
int		check_if_redirection(t_type_token type);
int		check_arguments(t_type_token type);
int		count_pipes(t_data *pointer);
int		new_tokens_count(t_data *pointer);
int		handle_strdup(t_data *pnt, int j, int k, char *value);
// int		count_characters(char const *s);
//
//==================[parser_merge_words.c]===================//
int		token_copy(t_data *pointer, t_token *tokens_new, int *i, int *j);
void	clean_double_pointer(char **pnt);
//
//==================[tokener_filling.c]===================//
int		word_filling(t_data *pntr, char const *str);
int		reallocate_tokens_if_max(t_data *pntr, int max_token);
int		word_filling(t_data *pntr, char const *s);
int		filling_quotes(t_data *pntr, char const *str, char tmp);
//==================[tokener.c]===================//
int		tokener(t_data *pntr);
//==================[extender.c]===================//
int 	extender(t_data *pntr);
int		dollar_replacement(char *string, char **value, t_data *pntr, int exception);
char	*value_of_variable(t_data *pntr, char *i);
int		variable_index(char **env, char *n);
//==================[extender_utils.c]===================//
int 	length_of_variable(const char *n);
int 	if_has(const char *n, char c);
int		substring_concatenation(char *string, char **pntr);
int		pipelines_redirect(t_data *pntr, int i, int *pip);
//==================[multiline.c]===================//
int		create_heredoc(t_data *pntr, t_tab_cmd *tab_cmd, int i);
//==================[signal.c]===================//
void	set_mode(t_data *pntr, t_set_mode mode);
//==================[find_exec.c]===================//
int 	find_exec(t_data *pntr, t_tab_cmd *cmd_tab);
//==================[cleaning.c]===================//
void	fd_cleaning(t_data *pntr, t_tab_cmd *tab_cmd, int i);
void	total_clean(t_data *pntr);
void	pntr_cleaning(t_data *pntr);
//==================[init.c]===================//
void    init_pntr(t_data *pntr, char **env);
//==================[exit_utils.c]===================//
void	free_string_array(char **pnt);
void	fd_exit(t_data *pntr, int code_exit);
int		ft_putstr_int(char *s, int fd);
//==================[env.c]===================//
int		increase_shlvl(t_data *pntr);

#endif
