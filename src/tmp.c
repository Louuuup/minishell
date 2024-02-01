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
		data->cmd->cmd = gc_split(commande, ' ');
	}

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
		printf("cmd: %s\n", cmd->cmd[0]);
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
	printf("is builtin: %d\n", cmd->built_in);
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