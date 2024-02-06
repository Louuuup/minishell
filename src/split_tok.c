#include "minishell.h"

void ft_splt_wrd_qte(size_t i, size_t *j, char *s)
{
    if(s[i] == '\'')
    {   
        *j += 1;
        while(s[i + *j] && s[i + *j] != '\'')
            *j+= 1;
		*j+= 1;
    }
    else  if(s[i] == '\"')
    {   
        *j += 1;
        while(s[i + *j] && s[i + *j] != '\"')
            *j += 1;
		*j += 1;
    }
    else 
        while(!ft_isspace(s[i + *j]) && s[i + *j] && s[i + *j] !='\'' && s[i + *j] !='\"')
            *j += 1;
		
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
		else
			return(ft_tokcount(tok, str));
    }
	return(0);
}

size_t	word_countq(char *s)
{
    t_countok	tok;

	tok.i = 0;
	tok.count = 0;
    tok.tok = false;
	tok.quotes = false;
	while(s[tok.i])
    	ft_boolcount(&tok, s);
	printf("%zu\n", tok.count);
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
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	j = 0;
	index = -1;
	while (++index < count)
	{
		while (s[i])
		{
			while (ft_isspace(s[i]))
				i++;
            ft_splt_wrd_qte(i, &j, s);
			split[index] = word_makerq(&s[i], (j));
			break ;
		}
		i = i + j;
		j = 0;
	}
	split[index] = NULL;
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
