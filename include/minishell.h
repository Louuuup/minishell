/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:27:09 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/20 13:37:54 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline.h>
# include <history.h>
# include <string.h>
# include <fcntl.h>

//==================VALUES===================//
# define DEBUG_ON 0
# define TRUE 1
# define FALSE 0
# define YES 1
# define NO 0
# define PROMPT_NAME "\033[35m\033[1mUser \033[0m\033[1m→ \033[0m"
//==================ERRORS===================//
# define ERR_MAIN "\033[31m\033[1mERROR > \033[0m"
# define ERR_EXP "\033[37m\033[1mREASON\033[0m"
# define ERR_FORK "Forked up!\n"
# define ERR_DUP "Dup error\n"
//==================Structs===================//

/**
 * NOTE: Simple command + args
*@param	argc Number of args.
*@param	argv Array of cmd + all its args.
*@param	next Next command.
*/
struct cmd;

typedef struct cmd
{
	int			argc;
	char		*cmd_path;
	char		**args;
	struct cmd	*next;
}			t_cmd;

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

typedef struct data
{
	char	*user_prompt; //to free
	// int		exit_promt;
}			t_data;
//
//==================[utils.c]===================//
t_data	*get_data(void);
void	ft_error(char *str);
void	my_error(char *str);
//
//==================[prompt.c]===================//
void	prompt_create(t_data *data);
//
//==================[builtin.c]===================//
void	built_echo(char **args, int argc, int fd_out);
void	build_pwd(int fd_out);
//
//==================[exec_utils.c]===================//
void	ft_dup2(int fd, int std);

#endif
