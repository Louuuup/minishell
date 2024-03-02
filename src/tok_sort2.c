#include "minishell.h"

int	ft_splt_wrd_qte(t_countok *tok, char *str)
{
	if (str[tok->i] == '>')
		return (ft_outtok(tok, str));
	if (str[tok->i] == '<')
		return (ft_intok(tok, str));
	else
		return (ft_wordtok(tok, str));
	return (0);
}

int	ft_boolcount(t_countok *tok, char *str)
{
	while (str[tok->i])
	{
		while (ft_isspace(str[tok->i]))
			tok->i++;
		if (str[tok->i] == '>')
			return (ft_outcount(tok, str));
		if (str[tok->i] == '<')
			return (ft_incount(tok, str));
		else if (str[tok->i])
		{
			tok->count++;
			return (ft_tokcount(tok, str));
		}
	}
	return (0);
}

size_t	word_countq(char *s)
{
	t_countok	tok;

	tok.i = 0;
	tok.count = 0;
	while (s[tok.i])
		ft_boolcount(&tok, s);
	return (tok.count);
}

int	tok_arg(char *str, t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->cmd[i])
		i++;
	ft_expansion(str, &tmp->cmd[i]);
	ft_removeqte(tmp->cmd[i]);
	tmp->cmd[i + 1] = NULL;
	tmp->ac++;
	return (1);
}

int	exp_qtes_bool(char *str, t_ibool *i, int pos)
{
	i->i = 0;
	i->single = false;
	i->dbl = false;
	while (i->i < pos && str[i->i])
	{
		if (str[i->i] == '\'')
			ft_sglbool(&i->single, &i->dbl);
		if (str[i->i] == '"')
			ft_dblbool(&i->single, &i->dbl);
		i->i++;
	}
	return (1);
}
