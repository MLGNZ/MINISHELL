/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:27 by tchevall          #+#    #+#             */
/*   Updated: 2025/08/27 19:14:21 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_var(int pos, t_ms *ms)
{
	t_list *curr;
	int i;

	if (pos == -1)
		return (getcwd(NULL, 0));
	curr = ms->lst_env;
	i = -1;
	while (++i < pos)
		curr = curr->next;
	return (curr->content);
}

static void	set_newvar(t_list *curr, char *pwd, int i, char *to_find)
{
	if (i == -1)
		return ;
	else
	{
		free(curr->content);
		curr->content = ft_strjoin(to_find, pwd);
	}
}

static void	update_env(t_ms *ms, char *oldpwd, char *newpwd)
{
	t_list *curr;
	int		i;

	curr = ms->lst_env;
	i = -1;
	while (++i <  my_get_env("PWD=", ms->lst_env))
		curr = curr->next;
	i = my_get_env("PWD=", ms->lst_env);
	set_newvar(curr, newpwd, i, "PWD=");
	i = -1;
	curr = ms->lst_env;
	while (++i < my_get_env("OLDPWD=", ms->lst_env))
		curr = curr->next;
	i = my_get_env("OLDPWD=", ms->lst_env);
	set_newvar(curr, oldpwd, i, "OLDPWD=");
}

void	cd(char *path, t_ms **ms)
{
    char *oldpwd;
    char *newpwd; 

    oldpwd = ft_strdup(get_var(my_get_env("PWD=", (*ms)->lst_env), *ms + 4));
    newpwd = getcwd(NULL, 0);
	if (!path)
	{
		chdir(get_var(my_get_env("HOME=", (*ms)->lst_env), *ms) + 4);
		perror("cd");
		update_env(*ms, oldpwd, newpwd);
		return ;
	}
    if (chdir(path) == -1)
    {
        perror("cd");
        free(oldpwd);
        return ;
    }
    if (!newpwd)
    {
        perror("getcwd");
        free(oldpwd);
        return ;
    }
    update_env(*ms, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
}

