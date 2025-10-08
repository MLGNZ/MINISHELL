#ifndef BUILT_IN_H
# define BUILT_IN_H

#include "../minishell.h"

//BUILT-IN
int		ft_export(char **args, t_ms *ms);
int		ft_unset(char **args, t_ms *ms);
void	cd(char **path, t_ms **env);
void	env(t_ms *ms, t_pl *pl);
int		echo(char **tab, t_ms *ms);
void	ft_exit(t_ms *ms, char **cmd_args, int in_child);
int		pwd(t_ms *ms);

#endif