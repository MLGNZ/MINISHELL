/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:58:18 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/09 13:22:52 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line			**split_and_init_lines(t_ms *ms, char **rline);
static int		line_len(char **rline, int *len);
static int		count_lines(char **rline, int *nb_of_lines);
static t_line	*make_line(char **rline, int len);

/*Je separe ma readline en lines, soit en splits contenant le contenu d'une line
soit une suite comprise entre deux operateurs de type && || ;
ou un subshell
Je renvoie donc un array de structures comprenant a ce stade juste un grand 
split contenant son machin
Je me dois d'indiauer des la creation dans makeline si il s'agit 
d'un subshell ou non*/
t_line	**split_and_init_lines(t_ms *ms, char **rline)
{
	t_line	**ret;
	t_line	**ret0;
	int		len;

	len = 0;
	count_lines(rline, &len);
	ret = malloc(sizeof(t_line *) * (len + 1));
	if (!ret)
		return (panic(ms, 52), NULL);
	ft_bzero(ret, sizeof(t_line *));
	ret0 = ret;
	while (rline && *rline && ((rline[1] || which_op(*rline) != SEMICOLON)))
	{
		*ret = make_line(&(*rline), line_len(rline, &len));
		if (!*ret++)
			return (panic(ms, 52), NULL);
		rline += len;
	}
	*ret = NULL;
	freesplit(ms->s_readline);
	ms->s_readline = NULL;
	return (ret0);
}

/*Je cree une structure line coomprenant le bon split
Si subshell, je fais un split comprenant tout l'interieur 
des parentheses
Je retire donc les parentheses et je mets un flag subshell a 1*/
static t_line	*make_line(char **rline, int len)
{
	t_line	*line;
	char	**ret;

	line = malloc(sizeof(t_line));
	if (!len || !line)
		return (free(line), NULL);
	ft_bzero(line, sizeof(t_line));
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (free(line), NULL);
	line->split_line_length = len;
	line->split_line = ret;
	if ((which_op(*rline) == SEMICOLON || which_op(*rline) == AND \
	|| which_op(*rline) == OR) && len-- && rline++)
		line->ctrl_op = which_op(*(rline - 1));
	else
		line->ctrl_op = 0;
	while (len--)
	{
		*(ret) = ft_strdup(*(rline++));
		if (!*ret++)
			return (freesplit(line->split_line), free(line), NULL);
	}
	return (*ret = NULL, line);
}

static int	count_lines(char **rline, int *nb_of_lines)
{
	int	len;
	int	line_l;

	line_l = 0;
	len = 0;
	while (rline && *rline && ((rline[1] || which_op(*rline) != SEMICOLON)))
	{
		line_l = line_len(rline, &len);
		(*nb_of_lines)++;
		rline += line_l;
	}
	return (*nb_of_lines);
}

static int	line_len(char **rline, int *len)
{
	int	p;

	*len = 0;
	p = 0;
	if (!rline || !*rline)
		return (0);
	while (rline && *rline)
	{
		if (which_op(*rline) == O_PAR)
			p++;
		if (which_op(*rline) == C_PAR)
			p--;
		rline++;
		(*len)++;
		if (!*rline || (!p && (which_op(*rline) == AND \
		|| which_op(*rline) == OR || which_op(*rline) == SEMICOLON)))
			break ;
	}
	return (*len);
}
