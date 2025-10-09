/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:27:34 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:20:14 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd(char**tab, t_ms *ms)
{
	char	*cmd_file;

	cmd_file = NULL;
	if (!tab)
		return (1);
	if (is_build_in(*tab))
		return (1);
	if (*tab && (**tab == '/' || **tab == '.' || **tab == '\0'))
		return (1);
	if (!find_file(*tab, &cmd_file, ft_getenv("PATH", ms), -1))
		return (0);
	if (!cmd_file)
		return (1);
	free(*tab);
	*tab = cmd_file;
	return (1);
}

int	is_build_in(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 5) || \
		!ft_strncmp(str, "cd", 3) || \
		!ft_strncmp(str, "pwd", 4) || \
		!ft_strncmp(str, "export", 7) || \
		!ft_strncmp(str, "unset", 6) || \
		!ft_strncmp(str, "env", 4) || \
		!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

static int	cat_over_quotes(const char *s0, char *s, char q);

void	remove_quotes(const char *s0, char *s)
{
	char	q;

	while (s && *s)
	{
		if (is_meta(s, '\'', (char *)s0))
			q = '\'';
		else if (is_meta(s, '\"', (char *)s0))
			q = '\"';
		else
			q = 0;
		if (q)
			s += cat_over_quotes(s, s, q);
		else
			s++;
	}
}

static int	cat_over_quotes(const char *s0, char *s, char q)
{
	int	len;

	len = 0;
	ft_strlcpy(s, s + 1, ft_strlen(s));
	while (*s)
	{	
		if (is_meta(s, q, (char *)s0))
		{
			len = (s - s0);
			break ;
		}
		s++;
	}
	ft_strlcpy(s, s + 1, ft_strlen(s));
	return (len);
}

void	remove_backslashes(const char *s0, char *s)
{
	while (s0 && *s)
	{
		if (*s == '\\')
			ft_strlcpy(s, s + 1, ft_strlen(s + 1) + 1);
		s++;
	}
}

char	is_meta(char *c_address, char meta, char *s0)
{
	if (*c_address == meta && (s0 == c_address \
		|| !(how_many_backslashes(s0, c_address) % 2)))
		return (meta);
	return (0);
}

char	meta_char(char *rline, char *rline0)
{
	if (is_meta(rline, '|', rline0))
		return ('|');
	else if (is_meta(rline, '\'', rline0))
		return ('\'');
	else if (is_meta(rline, '\"', rline0))
		return ('\"');
	return (0);
}

int	is_int(char *s)
{
	int	i;
	int	len;

	len = 0;
	i = -1;
	while (s[++i] && ft_isdigit(s[i]))
		len++;
	if (len < 10)
		return (len);
	else if (ft_strncmp(s, "2147483647", len) <= 0)
		return (len);
	return (0);
}

int	how_many_backslashes(char *s0, char *s)
{
	int	n;

	n = 0;
	while (s > s0)
	{
		s--;
		if (*s == '\\')
			n++;
		else
			break ;
	}
	return (n);
}

static int	which_op2(char *str);

int	which_op(char *str)
{
	if (!str && !*str)
		return (0);
	if (*str == '\n')
		return (EOL);
	if (!ft_strncmp(str, "||", 3))
		return (OR);
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	if (!ft_strncmp(str, "&&", 3))
		return (AND);
	if (!ft_strncmp(str, "&", 2))
		return (ESP);
	if (!ft_strncmp(str, ";", 2))
		return (SEMICOLON);
	if (!ft_strncmp(str, ";;", 3))
		return (DBSEMICOLON);
	if (!ft_strncmp(str, "(", 2))
		return (O_PAR);
	if (!ft_strncmp(str, ")", 2))
		return (C_PAR);
	return (which_op2(str));
}

static int	which_op2(char *str)
{
	int	len_int;

	len_int = is_int(str);
	if (!len_int && *str == '&')
		len_int = 1;
	if (!ft_strncmp(str + len_int, "<", 2))
		return (RIN);
	if (!ft_strncmp(str + len_int, ">", 2))
		return (ROUT);
	if (!ft_strncmp(str + len_int, "<<", 3))
		return (HDOC);
	if (!ft_strncmp(str + len_int, ">>", 3))
		return (AROUT);
	return (0);
}

int	is_var_ass(char *str)
{
	while (str && *str && *str != '=' && *str != '+')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	if (!*str)
		return (0);
	if (*str == '+' && *(str + 1) && *(str + 1) != '=')
		return (0);
	return (1);
}

int	cw(char *s0, int *len)
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
			s1 += word_length(s0, s1);
		}
	}
	return (*len = nw);
}

void	ambiguous_message(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

char	which_word(char *s, char *s0)
{
	char	ww;

	if (is_meta(s, '\'', s0))
		ww = '\'';
	else if (is_meta(s, '\"', s0))
		ww = '\"';
	else
		ww = ' ';
	return (ww);
}

int	is_ambiguous(char *exp)
{
	int	len;

	len = 0;
	if (cw(exp, &len) > 1)
		return (1);
	return (0);
}
