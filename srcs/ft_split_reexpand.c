/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_reexpand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:45:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 15:40:56 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*make_word(char *s0, int len);

//split the line into an array of 'words' and 'operators'

static int	word_length_re(char *s0, char *s)
{
	char	q;
	int		len;

	len = 0;
	while (*s && *s != ' ')
	{
		q = ' ';
		if (is_meta(s, '\'', s0))
			q = '\'';
		else if (is_meta(s, '\"', s0))
			q = '\"';
		len++;
		s++;
		while (*s && ((q == ' ' && *s != ' '\
		&& !is_meta(s, '\'', s0) && !is_meta(s, '\"', s0)) || (q != ' ' && \
		!(q == is_meta(s, '\'', s0) || q == is_meta(s, '\"', s0)))) && ++len)
			s++;
		if (*s && *s == q && q != ' ' && ++len)
			s++;
	}
	return (len);
}

static int	cw_re(char *s0, int *len)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s0;
	while (*s1)
	{
		if (*s1 == ' ')
				s1++;
		else
		{
			nw++;
			s1 += word_length_re(s0, s1);
		}
	}
	return (*len = nw);
}

char	**ft_split_reexpand(char *s0, int *len)
{
	char	**ret;
	char	**ret1;
	char	*s1;

	*len = 0;
	s1 = (char *)s0;
	cw_re(s0, len);
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
			*ret1 = make_word(s1, word_length_re(s1, s1));
			if (!(*(ret1++)))
				return (freesplit(ret), NULL);
			s1 += word_length_re(s0, s1);
		}
	}
	return (*ret1 = 0, ret);
}
