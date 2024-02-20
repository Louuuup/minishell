#include "minishell.h"

int tok_doc(char *str, t_idtok *id, t_cmd *tmp)
{
       ft_removeqte(str);
       ft_docadd_back(&tmp->doc, ft_lstnewdoc(str));
       tmp->in_flag = REDIR_HEREDOC;
       id->here = false; 
       return(1);
}