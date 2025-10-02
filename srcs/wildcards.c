/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/02 17:59:30 by tchevall         ###   ########.fr       */
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

static char	*emf_loop(char **ret_add, struct dirent *dirent, int is_dir)
{
	char	*ret;

	ret = *ret_add;
	ret = wild_join(ret, (char *)dirent->d_name);
	if (!ret)
		return (NULL);
	if (is_dir)
	{
		ret = ft_strjoin_free1(ret, "/");
		if (!ret)
			return (NULL);
	}
	return (*ret_add = ret);
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
