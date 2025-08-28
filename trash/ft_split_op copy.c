/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:45:54 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/15 16:16:17 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static char	*mkword(const char *s, char *s1, char *w, int op_l);
static int	cw(const char *s);
static int	is_op(const char *s, int beginning);

//split the line into an array of 'words' and 'operators'
char	**ft_split_op(char const *s, int *len)
{
	char	**ret;
	char	**ret1;
	char	*s1;

	s1 = (char *)s;
	*len = cw(s);
	printf("len %d\n", *len);
	if (!*len)
		return (NULL);
	ret = malloc(sizeof(char *) * (*len + 1));
	if (!ret)
		return (0);
	ret1 = ret;
	while (s && *s1)
	{
		while (*s1 && *s1 == ' ')
				s1++;
		if (!*s1)
			break ;
		*ret1 = mkword(s1, s1, 0, (is_op(s1, s == s1)));
		if (!*(ret1++))
			return (freesplit(ret), NULL);
		if (*s1 == '\'' && s1++ && s1++)
			while (*s1 && *(s1 - 1) != '\'')//unclosed quote ?
				s1++;
		else if (*s1 == '\"' && s1++ && s1++)
			while (*s1 && *(s1 - 1) != '\"')//unclosed quote ?
				s1++;
		else if (is_op(s1, s == s1))
			s1 += (is_op(s1, 1));
		else if (*s1)
			while (*s1 && !is_op(s1, s == s1) && *s1 != '\'' && *s1 != '\"' && *s1 != ' ')
				s1++;
	}
	*ret1 = 0;
	return (ret);
}

static char	*mkword(const char *s, char *s1, char *w, int op_l)
{
	char	*w0;

	if (op_l)
	{
		w = malloc(sizeof(char) * (op_l + 1));
		if (!w)
			return (0);
		w[op_l] = 0;
		while (op_l-- > 0)
			w[op_l] = s[op_l];
		return (w);
	}
	if (*s1 == '\'' && s1++ && s1++)
		while (*s1 && *(s1 - 1) != '\'')
			s1++;
	else if (*s1 == '\"' && s1++ && s1++)
		while (*s1 && *(s1 - 1) != '\"')
			s1++;
	else
		while (s1 && *s1 && !is_op(s1, s1 == s) && *s1 != '\'' && *s1 != '\"' && *s1 != ' ')
			s1++;
	w = malloc(sizeof(char) * (s1 - s + 1));
	if (!w)
		return (0);
	w0 = w + (s1 - s);
	*w0 = 0;
	while (s1-- > s)
		*(--w0) = *(s1);
	return (w);
}

static int	is_op(const char *s, int beginning)
{
	if (!beginning && *(s - 1) == '\\')
		return (0);
	if (!ft_strncmp(s, "|", 1))
		return (1);
	if (!ft_strncmp(s, ">>", 2))
		return (2);
	if (!ft_strncmp(s, ">", 1))
		return (1);
	if (!ft_strncmp(s, "<<", 2))
		return (2);
	if (!ft_strncmp(s, "<", 1))
		return (1);
	if ((beginning || *(s - 1) == ' ') && (ft_isdigit(*s) || *s == '&') && is_op((s + 1), 0) && (*s + 1) != '|')
		return (1 + is_op((s + 1), 0));
	return (0);
}

static int	cw(const char *s)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s;
	while (*s1)
	{
		while (*s1 && *s1 == ' ')
				s1++;
		if (*s1 == '\'' && ++nw && s1++ && s1++)
			while (*s1 && *(s1 - 1) != '\'')//unclosed quote ?
				s1++;
		else if (*s1 && *s1 == '\"' && ++nw && s1++ && s1++)
			while (*s1 && *(s1 - 1) != '\"')//unclosed quote ?
				s1++;
		else if (is_op(s1, s == s1) && ++nw)// && printf("%s\n", s1))
			s1 += is_op(s1, 1);
		else if (*s1 && ++nw)// && printf("%s\n", s1))
			while (*s1 && !is_op(s1, s == s1) && *s1 != '\'' && *s1 != '\"' && *s1 != ' ')
				s1++;
	}
	return (nw);
}
