/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:27:27 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/09 13:23:45 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_newvar(t_list **curr, char *pwd, char *to_find);
static void	update_env(t_ms *ms, char *oldpwd, char *newpwd);
static void	error_mess(char *msg, char *oldpwd);
static int	error_cd(DIR *file, char **path, t_ms **ms);

void	cd(char **path, t_ms **ms)
{
	char	*oldpwd;
	char	*newpwd;
	DIR		*file;

	oldpwd = getcwd(NULL, 0);
	if (!path[1])
	{
		if (chdir(get_var(my_get_env("HOME=", (*ms)->lst_env), *ms) + 5) == -1)
			perror("cd");
		newpwd = getcwd(NULL, 0);
		update_env(*ms, oldpwd, newpwd);
		return ;
	}
	if (!error_cd(file, path, ms))
	{
		free(oldpwd);
		return ;
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		error_mess("getcwd", oldpwd);
		return ;
	}
	(update_env(*ms, oldpwd, newpwd), free(oldpwd), free(newpwd));
}

static void	set_newvar(t_list **curr, char *pwd, char *to_find)
{
	t_list	*var;
	char	*final_wd;

	final_wd = ft_strjoin(to_find, pwd);
	var = ft_lstnew(final_wd);
	update_lst(curr, &var);
	ft_lstadd_back(curr, var);
}

static void	update_env(t_ms *ms, char *oldpwd, char *newpwd)
{
	t_list	*curr;

	curr = ms->lst_env;
	set_newvar(&curr, newpwd, "PWD=");
	set_newvar(&curr, oldpwd, "OLDPWD=");
}

static void	error_mess(char *msg, char *oldpwd)
{
	perror(msg);
	free(oldpwd);
}

static int	error_cd(DIR *file, char **path, t_ms **ms)
{
	file = opendir(path[1]);
	if (errno == ENOTDIR)
	{
		perror(path[1]);
		return (0);
	}
	closedir(file);
	if (chdir(path[1]) == -1)
	{
		(*ms)->exit_code = 1;
		perror(path[1]);
		return (0);
	}
	return (1);
}
