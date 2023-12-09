#include "../include/minishell.h"

//the func clean the memory of an array for tokens & fill it with 0s

int clean_token_array(t_token *array_tokens, int max_number_token, t_data *pntr)
{
    while (++max_number_token < pntr->count_token)
    {
        if (array_tokens[max_number_token].value)
        {
            free(array_tokens[max_number_token].value);
            array_tokens[max_number_token].value = NULL;
        }
    }
    free(array_tokens);
    array_tokens = NULL;
    return (1);
}

int word_filling(t_data *pntr, char const *str)
{
    
}

int reallocate_tokens_if_max(t_data *pntr, int max_token)
{
    t_token *new_tokens_array;

    new_tokens_array = ft_calloc(max_token * 2, sizeof(t_token));
    if (!new_tokens_array)
        return (error_out(pntr, 1));
    while (--max_token >= 0)
    {

    }
}