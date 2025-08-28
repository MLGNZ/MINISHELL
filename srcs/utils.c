/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:59:51 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 19:26:53 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	printsplit(char **split)
{
	if (!split)
		printf("none");
	while (split && *split)
	{
		printf("[%s]", *split);
		split++;
	}
	printf("\n");
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
