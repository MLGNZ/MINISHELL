/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_pattern_and_match.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:10:02 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:28:04 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**get_wild_pattern(char **s, int *first_n_last, int wc, int *check);
static void	get_wild_pattern2(int *i, char *temp_s, int *wc);
static int	first_and_last(char *str);

int			match_wild_pattern(char *d_name, char **wild_pattern, int fnl);
static int	iter_wild(char *d_name, char **wild_ptrn, int first_n_last, int i);

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

static int	first_and_last(char *str)
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

int	match_wild_pattern(char *d_name, char **wild_pattern, int fnl)
{
	int	i;

	if (!wild_pattern || !d_name || d_name[0] == '.')
		return (0);
	if (!*wild_pattern)
		return (1);
	i = 0;
	if (fnl == 1 || fnl == 3)
	{
		if (!ft_strncmp(wild_pattern[i], d_name, ft_strlen(wild_pattern[i])))
			d_name += ft_strlen(wild_pattern[i++]);
		else
			return (0);
	}
	if (iter_wild(d_name, wild_pattern, fnl, i))
		return (1);
	return (0);
}

static int	iter_wild(char *d_name, char **wild_ptrn, int first_n_last, int i)
{
	while (*d_name && wild_ptrn[i])
	{
		if (*(d_name + 1) && iter_wild(d_name + 1, wild_ptrn, first_n_last, i))
			return (1);
		if (!ft_strncmp(wild_ptrn[i], d_name, ft_strlen(wild_ptrn[i])))
			d_name += ft_strlen(wild_ptrn[i++]);
		else
			d_name++;
	}
	if (wild_ptrn[i])
		return (0);
	if (first_n_last == 2 || first_n_last == 3)
	{
		if (*d_name)
			return (0);
	}
	return (1);
}
