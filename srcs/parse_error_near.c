/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_near.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:16:09 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/10 12:24:45 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_there_a_parse_error_near(char **tb);
static int	parse_error_needed(int op, char **tb, int p_op, int i);
static int	parse_error(int operator, char *token);
static int	parenthesis(char **tb);

int	is_there_a_parse_error_near(char **tb)
{
	int	i;
	int	op;
	int	p_op;

	p_op = 0;
	if (!tb[0])
		return (1);
	op = which_op(tb[0]);
	if ((op == PIPE || op == SEMICOLON || op == DBSEMICOLON || op == AND || \
		op == OR || op == C_PAR || op == DBSEMICOLON || op == ESP))
		return (parse_error(op, tb[0]));
	if (!tb[1] && (op >= 3 && op <= 6))
		return (parse_error(EOL, 0));
	if (parenthesis(tb) == -1)
		return (0);
	i = 0;
	while (tb[0] && tb[++i])
	{
		op = which_op(tb[i]);
		if (!parse_error_needed(op, tb, p_op, i))
			return (0);
	}
	return (1);
}

static int	parse_error(int operator, char *token)
{
	if (operator == DBSEMICOLON || operator == ESP)
		ft_putstr_fd("minishell: syntax error near unsupported token `", 2);
	else
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (operator >= 3 && operator <= 6 && token \
		&& (ft_isdigit(*token) || *token == '&'))
		while (token && *token && (ft_isdigit(*token) || *token == '&'))
			printf("%c", *token++);
	else if (!token)
		printf("newline");
	else
		printf("%s", token);
	printf("\'\n");
	return (0);
}

static int	parse_error_needed(int op, char **tb, int p_op, int i)
{
	if (op == DBSEMICOLON || op == ESP)
		return (parse_error(op, tb[i]));
	if (i)
		p_op = which_op(tb[i - 1]);
	if (p_op == C_PAR && (!op || (op >= 3 && op <= 6)))
		return (parse_error(op, tb[i]));
	if (op == C_PAR && p_op && p_op != C_PAR)
		return (parse_error(op, tb[i]));
	if (op == O_PAR && (!p_op || (op >= 3 && op <= 6)))
		return (parse_error(op, tb[i]));
	if (p_op == O_PAR && (op == PIPE || op == AND \
						|| op == SEMICOLON || op == OR))
		return (parse_error(op, tb[i]));
	if ((op == O_PAR && p_op == C_PAR) || (op == C_PAR && p_op == O_PAR))
		return (parse_error(op, tb[i]));
	if ((op == PIPE || op == AND || op == SEMICOLON || op == OR) \
	&& (p_op == PIPE || p_op == AND || p_op == SEMICOLON || p_op == OR))
		return (parse_error(op, tb[i]));
	if (!tb[i + 1] && (op >= 3 && op <= 6))
		return (parse_error(EOL, 0));
	if ((p_op >= 3 && p_op <= 6) && op)
		return (parse_error(op, tb[i]));
	return (1);
}

static int	parenthesis(char **tb)
{
	int	i;
	int	op;
	int	count;

	count = 0;
	i = -1;
	while (tb[++i])
	{
		op = which_op(tb[i]);
		if (op == O_PAR)
			count++;
		else if (op == C_PAR)
			count--;
		if (count < 0)
			return (parse_error(op, tb[i]), -1);
	}
	return (count);
}
