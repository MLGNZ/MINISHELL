/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:01:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/25 16:20:55 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_read_line(char *rline0, char *rline);

static int	gvl_part2(t_ms *ms, char *rline, char **temp_spltd)
{
	while (!valid_read_line(rline, rline))
	{
		rl_on_new_line();
		signal(SIGINT, sig_handler_prompt);
		rline = ft_strjoin_free12(rline, readline("> "));
		if (!rline)
			return (0);
		if (g_sig)
		{
			ms->prev_exit_code = g_sig;
			dup2(ms->fd_in, 0);
			break ;
		}
		temp_spltd = ft_split_op(rline, &ms->s_readline_len);
		if (!is_there_a_parse_error_near(temp_spltd))
			return (add_history(rline), free(rline), freesplit(temp_spltd), -1);
		freesplit(temp_spltd);
	}
	signal(SIGINT, sig_handler);
	ms->s_readline = ft_split_op(rline, &ms->s_readline_len);
	if (!ms->s_readline)
		return (0);
	add_history(rline);
	free(rline);
	ms->readline = NULL;
	if (g_sig)
		return (2);
	return (1);
}

int get_valid_line_inter(t_ms *ms, int i)
{
	int	vl_value;
	
	while (1)
	{
		vl_value = get_valid_line(ms, i);
		if (!vl_value)
			return (0);
		else if (vl_value == 2)
			break ;
		if (!g_sig)
		{
			break;
		}
	}
	g_sig = 0;
	return (1);
}

int	get_valid_line(t_ms *ms, int i)
{
	char	*rline;
	char	**temp_spltd;

	while (1)
	{
		rl_on_new_line();
		rline = readline("minishell% ");
		if (!rline)
			return (panic(ms, 0));
		if (g_sig)
		{
			ms->prev_exit_code = g_sig;
			g_sig = 0;
		}
		temp_spltd = ft_split_op(rline, &ms->s_readline_len);
		if (!temp_spltd)
			return (printf("here"),panic(ms, 52));
		if (!is_there_a_parse_error_near(temp_spltd))
			return (add_history(rline), free(rline), freesplit(temp_spltd), -1);
		freesplit(temp_spltd);
		i = 0;
		while (rline[i] && rline[i] == ' ')
			i++;
		if (rline[i])
			break ;
		free(rline);
	}
	if (!rline)
		return (0);
	return (gvl_part2(ms, rline, temp_spltd));
}

/*devrais checker si il y a des parentheses ouvertes*/
/*refaire  avec la splitline */
static int	valid_read_line(char *rline0, char *rline)
{
	char	q;
	int		p;

	p = 0;
	q = 0;
	while (*rline)
	{
		if (q == '|' && *rline && *rline != ' ')
			q = 0;
		if (q && q == meta_char(rline, rline0))
			q = 0;
		else if (!q && *rline == is_meta(&(*rline), '(', rline0))
			p++;
		else if (!q && *rline == is_meta(&(*rline), ')', rline0))
			p--;
		else if (!q)
			q = meta_char(rline, rline0);
		rline++;
	}
	return ((!q) * !p);
}
