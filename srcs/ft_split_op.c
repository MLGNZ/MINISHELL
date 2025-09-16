/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:45:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/16 15:52:16 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static int	is_op(char *s0, char *s);
static char	*make_word(char *s0, int len);

//split the line into an array of 'words' and 'operators'
char	**ft_split_op(char *s0, int *len)
{
	char	**ret;
	char	**ret1;
	char	*s1;

	*len = 0;
	s1 = (char *)s0;
	cw(s0, len);
	ret = malloc(sizeof(char *) * (*len + 1));
	if (!ret)
		return (0);
	ret1 = ret;
	while (s0 && *s1)
	{
		if (*s1 == ' ')
				s1++;
		else
		{
			*ret1 = make_word(s1, word_length(s1, s1));
			if (!(*(ret1++)))
				return (freesplit(ret), NULL);
			s1 += word_length(s0, s1);
		}
	}
	return (*ret1 = 0, ret);
}

int	word_length(char *s0, char *s)
{
	char	q;
	int		len;

	len = 0;
	if (is_op(s, s))
		return (is_op(s, s));
	while (*s && *s != ' ' && !is_op(s0, s))
	{
		q = ' ';
		if (is_meta(s, '\'', s0))
			q = '\'';
		else if (is_meta(s, '\"', s0))
			q = '\"';
		len++;
		s++;
		while (*s && ((q == ' ' && *s != ' ' && !is_op(s0, s) \
		&& !is_meta(s, '\'', s0) && !is_meta(s, '\"', s0)) || (q != ' ' && \
		!(q == is_meta(s, '\'', s0) || q == is_meta(s, '\"', s0)))) && ++len)
			s++;
		if (*s && *s == q && q != ' ' && ++len)
			s++;
	}
	return (len);
}

int	is_redir_and_len(char *s0, char *s)
{
	int	is_esp;
	int	l_int;

	is_esp = 0;
	if (!s0 || !*s0)
		return (0);
	if (s0 != s && !(*(s - 1) == ' ' || is_meta(s - 1, '|', s0) \
	|| is_meta(s - 1, '&', s0) || is_meta(s - 1, '(', s0) \
	|| is_meta(s - 1, ')', s0) || is_meta(s - 1, '>', s0) \
	|| is_meta(s - 1, '<', s0) || is_meta(s - 1, ';', s0)))
		return (0);
	l_int = is_int(s);
	if (!l_int && is_meta(s, '&', s0) && (s == s0 || !is_meta(s - 1, '&', s0)))
		is_esp = 1;
	if (is_esp && *(s + 1) == '<' && *(s + 1) && *(s + 2) != '<')
		return (0);
	l_int += is_esp;
	if ((*(s + l_int) == '>' || *(s + l_int) == '<') && (*(s + l_int)))
		return (l_int + is_op(s0, s + l_int));
	return (0);
}

/*check if an operator is at s, and return its length. beginning is a flag
that's true if s is the beginning of a larger string
and false if somewhere inside a larger string
(aka is the byte before s accessible ?)*/
static int	is_op(char *s0, char *s)
{
	if ((how_many_backslashes(s0, s) % 2))
		return (0);
	if (!ft_strncmp(s, ">>", 2))
		return (2);
	if (!ft_strncmp(s, ">", 1))
		return (1);
	if (!ft_strncmp(s, "<<", 2))
		return (2);
	if (!ft_strncmp(s, "<", 1))
		return (1);
	if (!ft_strncmp(s, ";;", 2))
		return (2);
	if (!ft_strncmp(s, ";", 1))
		return (1);
	if (!ft_strncmp(s, "&&", 2))
		return (2);
	if (!ft_strncmp(s, "||", 2))
		return (2);
	if (!ft_strncmp(s, "|", 1))
		return (1);
	if (!ft_strncmp(s, "(", 1))
		return (1);
	if (!ft_strncmp(s, ")", 1))
		return (1);
	return (is_redir_and_len(s0, s));
}

//make a word of length len starting at s.
static char	*make_word(char *s, int len)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (++i < len)
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}
