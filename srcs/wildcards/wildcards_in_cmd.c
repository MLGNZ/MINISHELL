/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_in_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:55:23 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:26:40 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*mf_in_cmd(char **wd_sq, int f_n_l, int *chk, int is_dir);
static int		mf_loop_in_cmd(t_list **list, struct dirent *dirent, int isdir);

int	wildcards_expansion_in_cmd(char **s, t_list **lst)
{
	char	**wild_requ;
	char	**ret_tab;
	int		flags[3];
	t_list	*mf;

	flags[0] = 0;
	flags[1] = 1;
	flags[2] = 0;
	if (s && *s && **s && (*s)[ft_strlen(*s) - 1] == '/')
	{
		(*s)[ft_strlen(*s) - 1] = 0;
		flags[0] = 1;
	}
	wild_requ = get_wild_pattern(s, &flags[2], 0, &flags[1]);
	if (!flags[1])
		return (0);
	mf = mf_in_cmd(wild_requ, flags[2], &flags[1], flags[0]);
	if (!flags[1] || !handle_no_match(&mf, s, flags[0]))
		return (0);
	ft_lstadd_back(lst, mf);
	return (1);
}

static t_list	*mf_in_cmd(char **wd_sq, int f_n_l, int *chk, int is_dir)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*dirent;
	t_list			*ret;

	ret = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (freesplit(wd_sq), *chk = 0, NULL);
	dir = opendir(pwd);
	free(pwd);
	dirent = readdir(dir);
	while (dirent)
	{
		if (match_wild_pattern(dirent->d_name, wd_sq, f_n_l) \
		&& (!is_dir || dirent->d_type == 4))
			if (!mf_loop_in_cmd(&ret, dirent, is_dir))
				return (freesplit(wd_sq), *chk = 0, NULL);
		dirent = readdir(dir);
	}
	sort_wild(&ret);
	return (freesplit(wd_sq), closedir(dir), ret);
}

static int	mf_loop_in_cmd(t_list **list, struct dirent *dirent, int isdir)
{
	char	*ret;
	t_list	*new;

	ret = ft_strdup((char *)dirent->d_name);
	if (!ret)
		return (0);
	if (isdir)
	{
		ret = ft_strjoin_free1(ret, "/");
		if (!ret)
			return (0);
	}
	new = ft_lstnew(ret);
	if (!new)
		return (free(ret), 0);
	ft_lstadd_back(list, new);
	return (1);
}
