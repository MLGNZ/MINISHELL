/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_near.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:16:09 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/27 16:35:52 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_error(int operator, char *token, int is_unsupported);

int	parenthesis(char **tb)
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
			return (parse_error(op, tb[i], 0), -1);
	}
	return (count);
}

/*Donc...
si un operateur ou parenthese est apres une redirection
X Si deux parentheses differentes se touchent
Si deux operateurs (| || & && ;) se touchent 
X Si un operateur (| || & && ;) touche l'interieur d'une parenthese
X Si autre chose qu'un operateur (| || & && ;)
touche l'exterieur d'une parenthese
X Si la ligne commence par un operateur ou par une parenthese fermee
X Si & ou ;;*/
int	is_there_a_parse_error_near(char **tb)
{
	int	i;
	int	op;
	int	p_op;

	p_op = 0;
	op = which_op(tb[0]);
	if ((op == PIPE || op == SEMICOLON || op == DBSEMICOLON || op == AND || \
		op == OR || op == C_PAR || op == DBSEMICOLON || op == ESP))
		return (parse_error(op, tb[0], 0));
	if (!tb[1] && (op >= 3 && op <= 6))
			return (parse_error(EOL, 0, 0));
	if (parenthesis(tb) == -1)
		return (0);
	i = 0;
	while (tb[0] && tb[++i])
	{
		op = which_op(tb[i]);
		if (op == DBSEMICOLON || op == ESP)
			return (parse_error(op, tb[i], 1));
		if (i)
			p_op = which_op(tb[i - 1]);
		if (p_op == C_PAR && (!op || (op >= 3 && op <= 6)))
			return (parse_error(op, tb[i], 0));
		if (op == C_PAR && p_op && p_op != C_PAR)
			return (parse_error(op, tb[i], 0));
		if (op == O_PAR && (!p_op || (op >= 3 && op <= 6)))
			return (parse_error(op, tb[i], 0));
		if (p_op == O_PAR && (op == PIPE || op == AND \
							|| op == SEMICOLON || op == OR))
			return (parse_error(op, tb[i], 0));
		if ((op == O_PAR && p_op == C_PAR) || (op == C_PAR && p_op == O_PAR))
			return (parse_error(op, tb[i], 0));
		if ((op == PIPE || op == AND || op == SEMICOLON || op == OR) \
		&& (p_op == PIPE || p_op == AND || p_op == SEMICOLON || p_op == OR))
			return (parse_error(op, tb[i], 0));
		if (!tb[i + 1] && (op >= 3 && op <= 6))
			return (parse_error(EOL, 0, 0));
		if ((p_op >= 3 && p_op <= 6) && op)
			return (parse_error(op, tb[i], 0));
	}
	return (1);
}

char	*operator_code_to_string(int operator_code)
{
	if (operator_code == EOL)
		return ("newline");
	if (operator_code == PIPE)
		return ("|");
	if (operator_code == RIN)
		return ("<");
	if (operator_code == ROUT)
		return (">");
	if (operator_code == HDOC)
		return ("<<");
	if (operator_code == AROUT)
		return (">>");
	if (operator_code == SEMICOLON)
		return (";");
	if (operator_code == DBSEMICOLON)
		return (";;");
	if (operator_code == ESP)
		return ("&");
	if (operator_code == AND)
		return ("&&");
	if (operator_code == OR)
		return ("||");
	if (operator_code == O_PAR)
		return ("(");
	if (operator_code == C_PAR)
		return (")");
	return (0);
}

static int	parse_error(int operator, char *token, int is_unsupported)
{
	(void)is_unsupported;
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
