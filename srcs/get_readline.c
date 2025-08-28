/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:01:35 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 14:58:12 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_read_line(char *rline0, char *rline);

static int	gvl_part2(t_ms *ms, char *rline, char **temp_spltd)
{
	while (!valid_read_line(rline, rline))
	{
		rline = ft_strjoin_free12(rline, readline("> "));
		if (!rline)
			return (0);
		temp_spltd = ft_split_op(rline, &ms->s_readline_len);
		if (!is_there_a_parse_error_near(temp_spltd))
			return (add_history(rline), free(rline), freesplit(temp_spltd), -1);
		freesplit(temp_spltd);
	}
	ms->s_readline = ft_split_op(rline, &ms->s_readline_len);
	if (!ms->s_readline)
		return (0);
	add_history(rline);
	free(rline);
	ms->readline = NULL;
	return (1);
}

int	get_valid_line(t_ms *ms)
{
	char	*rline;
	int		i;
	char	**temp_spltd;

	i = -1;
	while (1)
	{
		rline = readline("minishell% ");
		if (!rline)
			return (panic(ms, 52));
		temp_spltd = ft_split_op(rline, &ms->s_readline_len);
		if (!temp_spltd)
			return (panic(ms, 52));
		if (!is_there_a_parse_error_near(temp_spltd))
			return (add_history(rline), free(rline), freesplit(temp_spltd), -1);
		freesplit(temp_spltd);
		i = -1;
		while (rline[++i])
			if (rline[i] != ' ')
				break ;
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
		if (q == '|' && *rline)
			q = 0;
		if (q && q == meta_char(rline, rline0))
			q = 0;
		if (!q && *rline == is_meta(&(*rline), '(', rline0))
			p++;
		else if (!q && *rline == is_meta(&(*rline), ')', rline0))
			p--;
		else if (!q)
			q = meta_char(rline, rline0);
		rline++;
	}
	return ((!q) * !p);
}
