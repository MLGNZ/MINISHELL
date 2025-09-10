/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/09 18:20:57 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*every_matching_files(char **wild_sequ, int first_n_last)
{
	char			*pwd;
	DIR				*dir;
	struct dirent	*dirent;
	char			*ret;

	ret = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	dir = opendir(pwd);
	free(pwd);
	while (1)
	{
		dirent = readdir(dir);
		if (!dirent)
			break ;
		if (match_wild_pattern(dirent->d_name, wild_sequ, first_n_last))
			ret = wild_join(ret, (char *)dirent->d_name);
	}
	freesplit(wild_sequ);
	closedir(dir);
	return (ret);
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

char	**get_wild_pattern(char **s, int *first_n_last)
{
	char	*temp_s;
	int		wc;
	int		len;
	int		i;
	char	**wild_requ;

	wc = 0;
	i = 0;
	temp_s = ft_strdup(*s);
	if (!temp_s)
		return (NULL);
	while (temp_s && (temp_s)[i])
		get_wild_pattern2(&i, temp_s, &wc);
	if (!wc)
		return (free(temp_s), NULL);
	*first_n_last = first_and_last(temp_s);
	wild_requ = ft_split_op(temp_s, &len);
	free(temp_s);
	i = -1;
	while (wild_requ[++i])
	{
		remove_quotes((wild_requ[i]), (wild_requ[i]));
		remove_backslashes(wild_requ[i], wild_requ[i]);
	}
	return (wild_requ);
}
