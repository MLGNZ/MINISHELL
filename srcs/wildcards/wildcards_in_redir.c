/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_in_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:11:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/10 12:27:27 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mf_in_redir(char **wild_sequ, int fst_n_lst, int *chk, int is_dir);
static char	*mf_loop_in_redir(char **ret_add, struct dirent *dirent, int isdir);

int	wildcards_in_redir(char **s)
{
	char	**wild_requ;
	char	*ret;
	int		flags[3];

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
	ret = mf_in_redir(wild_requ, flags[2], &flags[1], flags[0]);
	if (!flags[1])
		return (0);
	if (!ret)
		return (put_back_slash_at_the_end_if_necessary(s, flags[0]), 1);
	if (is_ambiguous(ret))
		return (free(ret), ambiguous_message(*s), 0);
	return (free(*s), *s = ret, 1);
}

static char	*mf_in_redir(char **wild_sequ, int fst_n_lst, int *chk, int is_dir)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*dirent;
	char			*ret;

	ret = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (freesplit(wild_sequ), *chk = 0, NULL);
	dir = opendir(pwd);
	free(pwd);
	dirent = readdir(dir);
	while (dirent)
	{
		if (match_wild_pattern(dirent->d_name, wild_sequ, fst_n_lst) \
		&& (!is_dir || dirent->d_type == 4))
			if (!mf_loop_in_redir(&ret, dirent, is_dir))
				return (freesplit(wild_sequ), *chk = 0, NULL);
		dirent = readdir(dir);
	}
	return (freesplit(wild_sequ), closedir(dir), ret);
}

static char	*mf_loop_in_redir(char **ret_add, struct dirent *dirent, int isdir)
{
	char	*ret;

	ret = *ret_add;
	ret = wild_join(ret, (char *)dirent->d_name);
	if (!ret)
		return (NULL);
	if (isdir)
	{
		ret = ft_strjoin_free1(ret, "/");
		if (!ret)
			return (NULL);
	}
	return (*ret_add = ret);
}

/*	flags[0] = directory;
	flags[1] = check;
	flags[2] = first_n_last; */
// int	wildcards_expansion_var(char **s)
// {
// 	char	**wild_requ;
// 	char	*ret;
// 	int		flags[3];

// 	flags[0] = 0;
// 	flags[1] = 1;
// 	flags[2] = 0;
// 	if (s && *s && **s && (*s)[ft_strlen(*s) - 1] == '/')
// 	{
// 		(*s)[ft_strlen(*s) - 1] = 0;
// 		flags[0] = 1;
// 	}
// 	wild_requ = get_wild_pattern(s, &flags[2], 0, &flags[1]);
// 	if (!flags[1])
// 		return (0);
// 	ret = matching_files(wild_requ, flags[2], &flags[1], flags[0]);
// 	if (!flags[1])
// 		return (0);
// 	if (!ret)
// 		return (put_back_slash_at_the_end_if_necessary(s, flags[0]), 1);
// 	return (free(*s), *s = ret, 1);
// }
