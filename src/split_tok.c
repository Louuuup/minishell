#include "minishell.h"

void ft_splt_wrd_qte(int i, int *j, char *s)
{
    if(s[i] == '\'')
    {   
        *j++;
        while(s[i + j] && s[i + j] != '\'')
            *j++;
    }
    else  if(s[i] == '\'')
    {   
        *j++;
        while(s[i + j] && s[i + j] != '\'')
            *j++;
    }
    else 
        while(!ft_isspace(s[i + j]))
            *j++;
    //while (s[i + j] != c && s[i + j] != '\0')
}

void    ft_boolcount(bool *tok, size_t *count, char *ch)
{
    static char c;

    if (*tok == false)
    {
        *count = *count + 1;
        *tok = true;
        if (*ch == '\'' || *ch == '"')
            c = *ch;
        else
            c = ' ';
        return ;
    }
    else if(c == *ch || (c == ' ' && ft_isspace(*ch)))
    {
        *tok = false;
        c = 0;
    }

}

size_t	word_count(char *s)
{
	size_t	i;
	size_t	count;
    bool    tok;

	i = 0;
	count = 0;
    tok = false;
    while(ft_isspace(s[i]))
        i++;
	while (s[i])
	{
        ft_boolcount(&tok, &count, &s[i]);
		i++;
	}
	return (count);
}

char	*word_maker(char *s, size_t len)
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

char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**splitter(char **split, char *s, size_t count)
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
			/*while (s[i + j] != c && s[i + j] != '\0')
				j++;*/
			split[index] = word_maker(&s[i], (j));
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
    
    flag = true;
	if (!s)
		return (NULL);
	count = word_count(s);
	if (count == 0 || ft_strlen(s) == 0)
	{
		split = (char **)malloc(sizeof(char *)); //modify with gc_malloc
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = (char **)malloc((word_count(s) + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	split = splitter(split, s, count);
	return (split);
}


# include <stdio.h>
# include <stdlib.h>
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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_strlen(const char *s)
{
	int	x;

	x = 0;
	if (s[0] == '\0')
		return (0);
	while (s[x] != '\0')
	{
		x++;
	}
	return (x);
}


void ft_splt_wrd_qte(int i, size_t *j, char *s)
{
    if(s[i] == '\'')
    {   
        j += 1;
        while(s[i + *j] && s[i + *j] != '\'')
            *j+= 1;
    }
    else  if(s[i] == '\'')
    {   
        *j += 1;
        while(s[i + *j] && s[i + *j] != '\'')
            *j += 1;
    }
    else 
        while(!ft_isspace(s[i + *j]))
            *j += 1;
    //while (s[i + j] != c && s[i + j] != '\0')
}

void    ft_boolcount(bool *tok, size_t *count, char *ch)
{
    static char c;

    if (*tok == false)
    {
        *count = *count + 1;
        *tok = true;
        if (*ch == '\'' || *ch == '"')
            c = *ch;
        else
            c = ' ';
        return ;
    }
    else if(c == *ch || (c == ' ' && ft_isspace(*ch)))
    {
        *tok = false;
        c = 0;
    }

}

size_t	word_count(char *s)
{
	size_t	i;
	size_t	count;
    bool    tok;

	i = 0;
	count = 0;
    tok = false;
    while(ft_isspace(s[i]))
        i++;
	while (s[i])
	{
        ft_boolcount(&tok, &count, &s[i]);
		i++;
	}
	return (count);
}

char	*word_maker(char *s, size_t len)
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

char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**splitter(char **split, char *s, size_t count)
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
            printf("first: %zu %zu\n", i, j);
            ft_splt_wrd_qte(i, &j, s);
			printf("%zu %zu\n", i, j);
			split[index] = word_maker(&s[i], (j));
            //printf("%s\n", split[index]);
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
	count = word_count(s);
	if (count == 0 || ft_strlen(s) == 0)
	{
		split = (char **)malloc(sizeof(char *)); //modify with gc_malloc
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = (char **)malloc((word_count(s) + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	split = splitter(split, s, count);
	return (split);
}


int main()
{
    char *str = " 'hello' yes sir 'one two' three four five";
    char **split;
    int i;

    i = 0;
    split = ft_split_tok(str);
    while(split[i]){
        printf("%s\n", split[i]);
        i++;    
    }
}