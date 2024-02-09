#include "minishell.h"

int ft_splt_wrd_qte(t_countok *tok, char *str)
{
        if (str[tok->i] == '\'')
			return(ft_sgltok(tok, str));
		if (str[tok->i] == '\"')
			return(ft_dbltok(tok, str));
		if (str[tok->i] == '>')
			return(ft_outtok(tok, str));
		if (str[tok->i] == '<')
			return(ft_intok(tok, str));
		else
			return(ft_wordtok(tok, str));
		return(0);
}
	 
int    ft_boolcount(t_countok *tok, char *str)
{
    while (str[tok->i])
    {
		while(ft_isspace(str[tok->i]))
			tok->i++;
        if (str[tok->i] == '\'')
			return(ft_sglcount(tok, str));
		if (str[tok->i] == '\"')
			return(ft_dblcount(tok, str));
		if (str[tok->i] == '>')
			return(ft_outcount(tok, str));
		if (str[tok->i] == '<')
			return(ft_incount(tok, str));
		else if(str[tok->i])
			return(ft_tokcount(tok, str));
    }
	
	return(0);
}

size_t	word_countq(char *s)
{
    t_countok	tok;

	tok.i = 0;
	tok.count = 0;
	while(s[tok.i])
    	ft_boolcount(&tok, s);
	return (tok.count);
}

char	*word_makerq(char *s, size_t len)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1)); //modify with gc_malloc
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = *s;
		s++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**splitterq(char **split, char *s, size_t count)
{
	t_countok tok;

	tok.i = 0;
	tok.j = 0;
	tok.count = 0;
	while (tok.count < count)
	{
		while (s[tok.i])
		{
			while (ft_isspace(s[tok.i]))
				tok.i++;
            ft_splt_wrd_qte(&tok, s);
			split[tok.count] = word_makerq(&s[tok.i], (tok.j));
			break ;
		}
		tok.i = tok.i + tok.j;
		tok.j = 0;
		tok.count++;
	}
	split[tok.count] = NULL;
	return (split);
}

char	**ft_split_tok(char *s)
{
	char	**split;
	size_t	count;
    
	if (!s)
		return (NULL);
	count = word_countq(s);
	if (count == 0 || ft_strlen(s) == 0)
	{
		split = (char **)malloc(sizeof(char *)); //modify with gc_malloc
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = (char **)malloc((word_countq(s) + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	split = splitterq(split, s, count);
	return (split);
}

void	cmd_status(t_cmd *cmd)
{
	if (DEBUG_ON)
		printf("(cmd_status) start\n");
	if (!cmd || !cmd->cmd)
	{
		printf("cmd: NULL\n");
		return ;
	}
	if (!cmd->cmd[0])
		printf("cmd: %s\n", "NULL");
	int i = 1;
	printf("args: ");
	if (!cmd->cmd[i])
		printf("NULL\n");
	while(cmd->cmd[i])
	{
		printf("cmd: %s\n", cmd->cmd[i]);
		i++;
	}
	printf("\n");
	if (cmd->built_in)
		printf("is builtin: TRUE\n");
	if (cmd->index)
		printf("index: %d\n", cmd->index);
	if (cmd->infile)
		printf("infile: %s\n", cmd->infile);
	if (cmd->outfile)
		printf("outfile: %s\n", cmd->outfile);
	if (cmd->in_flag)
		printf("in_flag: %d\n", cmd->in_flag);
	if (cmd->out_flag)
		printf("out_flag: %d\n", cmd->out_flag);
	if (cmd->fd_in)
		printf("fd_in: %d\n", cmd->fd_in);
	if (cmd->fd_out)
		printf("fd_out: %d\n", cmd->fd_out);
	printf("\n\n");
	if (cmd->next)
		cmd_status(cmd->next);
}