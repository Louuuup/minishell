
#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "struct.h"

int		ft_execute(t_info *info);
char	*truepath(char *cmd, char **env);
void	free_cmdpath(char **s_path, char **s_cmd);
char	*pathfinder(char **env);
char	*ft_strjoinslash(char const *s1, char const *s2);
t_cmd	*ft_lstnewcmd(char *cmd);
int 	ft_temptakecommand(int argc, char **argv, t_info *info);
void 	ft_cmdloop(t_info *inf);
int 	ft_inputredir(t_cmd *cmd);
int		ft_outputredir(t_cmd *cmd);
int		ft_stdin(t_cmd *cmd);
int 	ft_infile(t_cmd *cmd);
int 	ft_heredoc(t_cmd *cmd);
int 	ft_stdout(t_cmd *cmd);
int 	ft_infile(t_cmd *cmd);
int 	ft_heredoc(t_cmd *cmd);
int 	ft_outfile(t_cmd *cmd);
int 	ft_append(t_cmd *cmd);
int 	ft_makedoc(t_cmd *cmd);
int 	ft_editdoc(int fd, t_cmd *cmd);
#endif