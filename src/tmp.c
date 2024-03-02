#include "minishell.h"

void tmp_parse(t_data *data)
{
	//
	if (DEBUG_ON)
		printf("(tmp_parse) user_prompt: %s\n", data->user_prompt);
	if (!ft_strncmp(data->user_prompt, "test 1", 6))
	{
		char *commande = "echo test 1";
		data->cmd = gc_calloc(1, sizeof(t_cmd));
		if (data->cmd == NULL)
			error_str("malloc error\n");
		data->cmd->cmd = gc_split(commande, ' ');
	}
}
void	cmd_status(t_cmd *cmd)
{
	if (DEBUG_ON)
	{
		dprintf(1, "========================\n");
		dprintf(1, "     COMMAND STATUS     \n");
		dprintf(1, "========================\n");
	}
	if (!cmd || !cmd->cmd)
	{
		dprintf(1, "cmd: NULL\n");
		return ;
	}
	if (cmd->cmd[0])
		dprintf(1, "cmd:%sa\n", cmd->cmd[0]);
	int i = 1;
	if (!cmd->cmd[i])
		dprintf(1, "args: NULL\n");
	while(cmd->cmd[i])
	{
		dprintf(1, "args: %s\n", cmd->cmd[i]);
		i++;
	}
	dprintf(1, "\n");
	if (cmd->built_in)
		dprintf(1, "is builtin: TRUE\n");
	if (cmd->path)
		dprintf(1, "path: %s\n", cmd->path);
	if (cmd->index == 0)
		dprintf(1, "index: %d\n", cmd->index);	
	if (cmd->index)
		dprintf(1, "index: %d\n", cmd->index);
	if (cmd->infile)
		dprintf(1, "infile: %s\n", cmd->infile);
	if (cmd->outfile)
		dprintf(1, "outfile: %s\n", cmd->outfile);
	if (cmd->in_flag)
		dprintf(1, "in_flag: %d\n", cmd->in_flag);
	if (cmd->out_flag)
		dprintf(1, "out_flag: %d\n", cmd->out_flag);
	dprintf(1, "fd_in: %d\n", cmd->fd_in);
	if (cmd->fd_out == 0)
		cmd->fd_out = 1;
	dprintf(1, "fd_out: %d\n", cmd->fd_out);
	dprintf(1, "\n\n");
	if(cmd->doc)
	{	
		dprintf(1, "EOF: %s\n", cmd->doc->eof);
		while(cmd->doc->next)
		{
			cmd->doc = cmd->doc->next;
			dprintf(1, "EOF: %s\n", cmd->doc->eof);
		}
	}
	if (cmd->next)
	{
		dprintf(1, "next cmd:\n");
		cmd_status(cmd->next);
	}
	dprintf(1, "========================\n");

}
