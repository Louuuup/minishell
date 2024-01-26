
#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int 	ft_echo(char **cmd);
int		ft_pwd(void);
int		ft_executebuiltin(t_info *inf);
int		ft_env(char **env);
int		ft_cd(char **cmd, char **env);
char	*ft_findhome(char **env);
int		ft_unset(t_info *inf);
char	**unset_var(t_info *inf, int unset_index);
int		env_finder(char *str, char **env);
int 	export(t_info *inf);
int		env_len(char **env);
int 	ft_dupenv(char **dup_env, char **env);
int		ft_hasequal(char *str);
int		ft_strcmp_equal(const char *s1, const char *s2);

#endif