/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:27:09 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/22 19:38:54 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>

//==================VALUES===================//
# define DEBUG_ON 0
# define TRUE 1
# define FALSE 0
# define YES 1
# define NO 0
//==================ERRORS===================//
# define ERR_MAIN "\033[31m\033[1mERROR > \033[0m"
# define ERR_EXP "\033[37m\033[1mREASON\033[0m"
//==================Structs===================//

/**
 * NOTE: Simple command + args
*@param	argc Number of args.
*@param	argv Array of cmd + all its args.
*@param	next Next command.
*/
// struct cmd;

typedef struct cmd
{
	int			argc;
	char		**args;
	struct cmd	*next;
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
	t_token	*redirections;
	int		num_redirections;
	int		num_args;
	int		is_child_process;
	char	*last_multiline;
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		in_file;
	int		out_file;
}	t_tab_cmd;

typedef struct s_data
{
	t_token		*tokens;
	int			count_token;
	t_tab_cmd	*cmdt;
	int			code_exit;
	int			cmdt_count;
	int			count_pipes;
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
//
//==================[t_utils.c]===================//

int		check_arguments(t_type_token type);

#endif
