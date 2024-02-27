#include "minishell.h"

int incr_symb(char *str , t_expand *exp)
{
	exp->symb = true;
	exp->name[exp->j++] = str[exp->i++];
	exp->name[exp->j] = '\0';
	return (1);
}

int incr_exp(t_expand *exp)
{
	exp->i++;
	exp->init++;
	return (1);
}