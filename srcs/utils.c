/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:59:51 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 03:24:30 by tchevall         ###   ########.fr       */
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
