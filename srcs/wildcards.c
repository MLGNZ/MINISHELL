/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 17:01:27 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 16:33:26 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*matching_files_in_list(char **wd_sq, int f_n_l, int *chk, int is_dir)
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
			if (!emf_loop_in_loop(&ret, dirent, is_dir))
				return (freesplit(wd_sq), *chk = 0, NULL);
		dirent = readdir(dir);
	}
	sort_wild(&ret);
	return (freesplit(wd_sq), closedir(dir), ret);
}

char	*matching_files(char **wild_sequ, int fst_n_lst, int *chk, int is_dir)
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
			if (!emf_loop(&ret, dirent, is_dir))
				return (freesplit(wild_sequ), *chk = 0, NULL);
		dirent = readdir(dir);
	}
	return (freesplit(wild_sequ), closedir(dir), ret);
}

int	first_and_last(char *str)
{
	int	ret;

	ret = 0;
	if (!str)
		return (ret);
	if (*str != ' ')
		ret += 1;
	if (str[ft_strlen(str) - 1] != ' ')
		ret += 2;
	return (ret);
}

static void	get_wild_pattern2(int *i, char *temp_s, int *wc)
{
	char	ww;

	ww = which_word(&(temp_s)[(*i)], temp_s);
	if ((temp_s)[(*i)] == ' ')
		while ((temp_s)[(*i)] == ' ')
			(*i)++;
	else if ((ww == '\'' || ww == '\"') && ++(*i))
		while ((temp_s)[(*i)] && which_word(&(temp_s)[(*i)++], temp_s) != ww)
			(void)i;
	else if (is_meta(&(temp_s)[(*i)], '*', temp_s))
	{
		(temp_s)[(*i)++] = ' ';
		*wc = 1;
	}
	else
		(*i)++;
}

char	**get_wild_pattern(char **s, int *first_n_last, int wc, int *check)
{
	char	*temp_s;
	int		len;
	int		i;
	char	**wild_requ;

	i = 0;
	temp_s = ft_strdup(*s);
	if (!temp_s)
		return (*check = 0, NULL);
	while (temp_s && (temp_s)[i])
		get_wild_pattern2(&i, temp_s, &wc);
	if (!wc)
		return (free(temp_s), NULL);
	*first_n_last = first_and_last(temp_s);
	wild_requ = ft_split_op(temp_s, &len);
	if (!wild_requ)
		return (free(temp_s), *check = 0, NULL);
	i = -1;
	while (wild_requ[++i])
	{
		remove_quotes((wild_requ[i]), (wild_requ[i]));
		remove_backslashes(wild_requ[i], wild_requ[i]);
	}
	return (free(temp_s), wild_requ);
}
