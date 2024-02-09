#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
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
# define MINISHELL_ERR "\033[31m\033[1mminiSHELL: \033[0m"
# define PROMPT_NAME "\033[35m\033[1mminiSHELL \033[0m\033[1m→ \033[0m"
# define EXPORT_PREFIX "declare -x "
//==================Structs===================//

//base for command struct can be modified if needed
typedef struct s_cmd
{
	char			**cmd;
	char			*token;
	int 			ac; //argc
	int				index;
	pid_t			pid;
	int				fd_in; //default = STDIN_FILENO(0)
	int				fd_out; //default = STDOUT_FILENO(1)
	int 			in_flag; //redir_flag
	int				out_flag; //redir_flag
	char 			*infile; //path to file
	char			*outfile; //path to file
	struct s_cmd	*next;
	bool			built_in;
}			t_cmd;

//structs used for parsing

typedef struct s_tok
{
	char 	**cmd_list;
	char 	**sgl_cmd;
}			t_tok;

typedef struct s_idtok
{
	int		i;
	size_t		cmd_size;
	bool	out;
	bool	app;
	bool	here;
	bool	in;
	bool 	cmd;
}		t_idtok;

typedef struct s_countok
{
	size_t 	i;
	size_t 	j;
	size_t  count;
}			t_countok;

//chainlist for allocated memory blocks (for garbage collector)
typedef struct s_memblock
{
	void				*ptr;
	struct s_memblock	*next;
}				t_memblock;


typedef struct s_data
{
	t_cmd		*cmd;
	char		**env; //environnement, allocated and dynamicly updated (no garbo)
	char		*user_prompt; //prompt entered by user. (no garbo)
	int			code_exit;
	t_tok		parser;	//struct used for parsing
	t_memblock	*memblock; //head of allocated memory blocks
}				t_data;

//flag for redirection
enum e_redir_type
{
	REDIR_NONE, 	 //stdin stdout
	REDIR_INPUT,	 // <
	REDIR_OVERWRITE, // >
	REDIR_APPEND,	 // >>
	REDIR_HEREDOC,	 // <<
	REDIR_PIPE		 // |
};



//==================init.c===================//

void	init_all(t_data *data, char **envp);
//==================utils.c===================//

// strdup with garbage collector
char *gc_strdup(char *str);
// split with garbage collector
char **gc_split(char *str, char c);
//==================t_utils.c===================//

t_data	*get_data(void);
//==================parsing_main.c===================//

int		parser(t_data *data);
int		tokener(t_data *data);

//==================pipe_parsing.c===================//

int		ft_pipeparse(char *str);
void    ft_sglbool(bool *single, bool *dbl);
void    ft_dblbool(bool *single,bool *dbl);
//==================parsing_utils.c===================//

//check if there's  any unclosed quote
int 	ft_closedquote(char *str);
//splits on delim by adding 0 inside the string without malloc
char    *ft_strtok(char *str, const char delim);
size_t 	ft_cmdcount(char *str);

//==================tokenizer.c===================//

int id_tok(char *str, t_idtok *id, t_data *data);
int parsing(char **str, t_data *data);
int	token_maker(t_data *data);

//==================split_tok.c===================//

int 	ft_splt_wrd_qte(t_countok *tok, char *str);
char	**ft_split_tok(char *s);
char	**splitterq(char **split, char *s, size_t count);
char	*word_makerq(char *s, size_t len);
size_t	word_countq(char *s);

//==================count_tok.c===================//

int ft_sglcount(t_countok *tok, char *str);
int ft_dblcount(t_countok *tok, char *str);
int ft_outcount(t_countok *tok, char *str);
int ft_incount(t_countok *tok, char *str);
int ft_tokcount(t_countok *tok, char *str);

//==================split_tok_utils.c===================//

int ft_sgltok(t_countok *tok, char *str);
int ft_dbltok(t_countok *tok, char *str);
int ft_outtok(t_countok *tok, char *str);
int ft_intok(t_countok *tok, char *str);
int ft_wordtok(t_countok *tok, char *str);

//==================token_id.c===================//

int ft_idheredoc(t_idtok *id);
int ft_idinput(t_idtok *id);
int ft_idappend(t_idtok *id);
int ft_idoutput(t_idtok *id);
int ft_id_cmd_file_arg(char *str, t_idtok *id,t_data *data);
void	ft_builtincheck(t_cmd *cmd);
//==================linked_utils.c===================//

t_cmd	*ft_lstnewcmd(void);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new_cmd);
//==================tokenizer.c===================//

int		tokenizer(t_data *data);
//==================exec_main.c===================//

void	exec_main(t_data *data);
//==================exec_utils.c===================//

void	exec_cmd(t_data *data);
int		ft_pipe(t_cmd *cmd);
int		ft_dup2(t_cmd *cmd);
int		fd_redirect(int fd, char *file, int redir_flag);
//==================garbage_handler.c===================//

//adds a block on top of the list
t_memblock	*memblock_add(t_memblock *memblock, void *ptr);
//frees all the blocks in the list
void		gc_free(t_memblock *memblock);
//==================garbage_tools.c===================//

//works like malloc but adds the pointer to the memblock list
void		*gc_malloc(size_t size);
//works like calloc but adds the pointer to the memblock list
void		*gc_calloc(size_t count, size_t size);
//works like strjoin but adds the pointer to the memblock list
char *gc_strjoin(char *s1, char *s2);
//==================error_handler.c===================//

int		shell_error(void);
int		error_str(char *str);
//======================tmp.c=========================//

//tmp function to test parser and tokener
void tmp_parse(t_data *data);
//tmp function to print the cmd infos.
void cmd_status(t_cmd *cmd);
//====================builtin_env.c====================//

void	b_env(t_cmd *cmd);
// fetches a variable from the environment(no allocation)
char	*get_var(char **env, char *var);
char    **add_var(char **env, char *var, char *value);
char	*set_var(char **env, char *var, char *value);

//====================builtin_cd.c====================//

void    b_cd(t_cmd *cmd);
void    b_pwd(t_cmd *cmd);
//====================builtin_echo.c====================//

void    b_echo(t_cmd *cmd);
//====================builtin_echo.c====================//

void    b_unset(t_cmd *cmd);
//====================builtin_export.c====================//

void    b_export(t_cmd *cmd);
//====================builtin_utils.c====================//

int export_valid(char *str);
char *var_name(char *str);
#endif
