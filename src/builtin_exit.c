#include "minishell.h"

void b_exit(t_cmd *cmd)
{
    (void)cmd;
    if (DEBUG_ON)
        printf("(b_exit) b_exit called\n");
    gc_free_all(get_data()->memblock);
    exit(get_data()->code_exit);
}