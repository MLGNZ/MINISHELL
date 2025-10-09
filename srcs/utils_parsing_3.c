/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:27:34 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 18:26:30 by mlagniez         ###   ########.fr       */
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

int	is_var_ass(char *str)
{
	if (str && ft_isdigit(*str))
		return (0);
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
