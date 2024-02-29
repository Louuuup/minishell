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
# define MINISHELL_ERR "MINIshell: "
# define PROMPT_NAME "MINIshell~~> "
# define EXPORT_PREFIX "declare -x "
# define C_FIND	"\"\'<> \t\n\v\f\r"

//==================Structs===================//

typedef struct s_strtok
{
	char		*output;
	bool		found;
	char		quote;
}	t_strtok;

typedef struct s_ibool
{
	int 	i;
	bool    single;
    bool    dbl;
}		t_ibool;

typedef struct s_doc
{
	bool			expand;
	int 			index;
	char			*eof;
	char			*name;
	struct s_doc	*next;
}		t_doc;

//base for command struct can be modified if needed
typedef struct s_cmd
{
	char			**cmd;
	char			*token;
	char			*path;
	int 			ac; //argc
	int				index;
	pid_t			pid;
	int				fd_in; //default = STDIN_FILENO(0)
	int				fd_out; //default = STDOUT_FILENO(1)
	int 			in_flag; //redir_flag
	int				out_flag; //redir_flag
	char 			*infile; //path to file
	char			*outfile; //path to file
	t_doc			*doc;	//linked list for heredoc
	struct s_cmd	*next;
	bool			built_in;
}			t_cmd;

//structs used for parsing

typedef struct s_tok
{
	char 	**cmd_list;
	char 	**sgl_cmd;
	char	***free;
}			t_tok;

typedef struct s_idtok
{
	int		i;
	size_t	cmd_size;
	bool	out;
	bool	app;
	bool	here;
	bool	in;
	bool 	cmd;
}		t_idtok;

typedef struct s_expand
{
	char	*tmp;
	char    *str;
	char	*name;
	char	*var;
	int		i;
	int 	j;
	int     h;
	int		init;
	bool	symb;
}		t_expand;

typedef struct s_countok
{
	char 	*tmp;
	bool	onqtes;
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
	int 		hd_count; //heredoc count
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
int 	setcmdlist(t_data *data);
//==================pipe_parsing.c===================//

int		iboolinit(t_ibool *ibool);
int		ft_pipeparse(char *str);
void    ft_sglbool(bool *single, bool *dbl);
void    ft_dblbool(bool *single,bool *dbl);
//==================parsing_utils.c===================//

void	ft_strtokut(t_strtok *tok, char *stock);
void	ft_strtokinit(t_strtok *tok);
int 	ft_closedquote(char *str);
char    *ft_strtok(char *str, const char delim);
size_t 	ft_cmdcount(char *str);
//==================tokenizer.c===================//

int id_tok(char *str, t_idtok *id, t_data *data);
int parsing(char **str, t_data *data);
int	token_maker(t_data *data);
int	tokenizer(t_data *data);
//==================split_tok.c===================//

char	**ft_split_tok(char *s);
char	**splitterq(char **split, char *s, size_t count);
char	*word_makerq(char *s, size_t len);
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

//==================tok_sort.c===================//

int ft_id_cmd_file_arg(char *str, t_idtok *id,t_data *data);
int tok_app(char *str, t_idtok *id, t_cmd *tmp);
int tok_in(char *str, t_idtok *id, t_cmd *tmp);
int tok_out(char *str, t_idtok *id, t_cmd *tmp);
int tok_cmd(char *str, t_idtok *id, t_cmd *tmp);
//==================tok_sort2.c===================//

size_t	word_countq(char *s);
int	ft_boolcount(t_countok *tok, char *str);
int	ft_splt_wrd_qte(t_countok *tok, char *str);
int tok_arg(char *str, t_cmd *tmp);
int exp_qtes_bool(char *str, t_ibool *i, int pos);
//==================tok_sort_doc.c===================//

int tok_doc(char *str, t_idtok *id, t_cmd *tmp);
int checkqtesdoc(char *str);
//==================linked_utils.c===================//

t_cmd	*ft_lstnewcmd(void);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new_cmd);
void 	ft_clearcmdlst(t_cmd **lst);
//==================expansion.c===================//

int	ft_init_exp(t_expand *exp, int in, char *str);
int ft_expansion(char *str, char **final);
int ft_expand(int in, char *str, char **final);
int ft_expcat(t_expand *exp, char **final);
int ft_checksecexp(char *str, int i);
//==================expcat_utils.c===================//

int exp_symb(t_expand *exp);
int explencheck(char *str, char *var);
int exp_novar(t_expand *exp);
int exp_early_str(t_expand *exp);
int exp_var(t_expand *exp);

//==================exp_utils.c===================//

int incr_exp(t_expand *exp);
int incr_symb(char *str , t_expand *exp);
//==================parsingerror.c===================//

int unclosedqtes(t_data *data);
int pipeerr(t_data *data);
//==================docquotes.c===================//

t_doc	*ft_lstnewdoc(char *str);
t_doc	*ft_doclast(t_doc *lst);
void	ft_docadd_back(t_doc **lst, t_doc *new_cmd, int qts);
void	ft_cleardoclst(t_doc **lst);
//==================removequotes.c===================//

int		ft_removeqte(char *str);
void	inittmp(t_countok *tmp, char *str);
void	ft_dblboolqte(bool *single,bool *dbl, t_countok *tmp);
void	ft_sglboolqte(bool *single, bool *dbl, t_countok *tmp);
//==================ft_freeparse.c===================//

int 	ft_freeparse(t_data *data);
void	*ft_free_2darray(char **array);
void 	*ft_free3darray(char ***array);
//==================exec_main.c===================//

int		redirect_check(t_cmd *cmd);
void	exec_main(t_data *data);
void	exec_cmd(t_cmd *cmd);
//==================exec_utils.c===================//

int		ft_pipe(t_cmd *cmd);
int		ft_dup2(t_cmd *cmd);
int		fd_redirect(int fd, char *file, int redir_flag);
int		command_valid(t_cmd *cmdt, char *cmd);
//==================garbage_handler.c===================//

//adds a block on top of the list
t_memblock	*memblock_add(t_memblock *memblock, void *ptr);
//frees all the blocks in the list
void		gc_free_one(t_memblock *memblock, void *ptr);
void		gc_free_all(t_memblock *memblock);
//==================garbage_tools.c===================//

//works like malloc but adds the pointer to the memblock list
void		*gc_malloc(size_t size);
//works like calloc but adds the pointer to the memblock list
void		*gc_calloc(size_t count, size_t size);
//works like strjoin but adds the pointer to the memblock list
char *gc_strjoin(char *s1, char *s2);
//==================error_handler.c===================//

int		error_str_file(char *str, char *file);
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
char	**rm_var(t_data *data, char *var);

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
char *var_value(char *str);
//====================builtin_exit.c====================//

//====================signal_handler.c====================//

void sig_inthandler(int i);
#endif
