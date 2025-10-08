/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 19:39:02 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 20:32:32 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	incr_shlvl(t_list **env, t_ms *ms)
{
	char	*val;
	char	*new_sh;
	char	*shlvl;
	t_list	*sh_lst;

	if (my_get_env("SHLVL", *env) == -1)
		return ;
	shlvl = get_var(my_get_env("SHLVL", *env), ms);
	val = ft_itoa(ft_atoi(shlvl + 6) + 1);
	if (!val)
		panic(ms, 52);
	new_sh = ft_strjoin_free2("SHLVL=", val);
	if (!new_sh)
		panic(ms, 52);
	sh_lst = ft_lstnew(new_sh);
	if (!sh_lst)
		panic(ms, 52);
	if (!update_lst(&ms->lst_env, &sh_lst))
		panic(ms, 52);
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

void	get_status(int status, t_ms *ms)
{
	if (WIFEXITED(status))
	{
		ms->exit_code = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		ms->exit_code = WTERMSIG(status) + 128;
		if (ms->exit_code == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}
