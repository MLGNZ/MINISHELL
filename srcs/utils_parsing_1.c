/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:27:34 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 14:42:36 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
