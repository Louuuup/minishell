/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:27:09 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/15 14:21:16 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline.h>

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
struct cmd;

typedef struct cmd
{
	int			argc;
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

}			t_data;
//
//==================[utils.c]===================//
t_data	*get_data(void);
void	ft_error(char *str);
void	my_error(char *str);
//
//==================[t_utils.c]===================//

#endif
