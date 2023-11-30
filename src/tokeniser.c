#include "../include/minishell.h"

//'tokeniser' breaks the input by spaces, quotes, special characters;
//allocate memory for these tokens;
//also it checks syntax. A token has 3 variables:
//TYPE (which one?),
//VALUE (is there speacial characters?),
//NO_SPACE (followed by token to be concatenated?)

int tokeniser(t_data *pntr)
{
	int	i;

	i = 0;
	pntr->tokens = ft_calloc(pntr->max_token, sizeof(t_token));
	if (!pntr->tokens)
		return (error_out(pntr, 1));
	while (pntr->input[++i])
		if (function_to_fill_with_tokens(pntr, &i, 0) == 1)
			return (1);
	return (function_to_check_the_syntax(pntr));
}
