// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   split_and_init_lines.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/16 15:10:01 by mlagniez          #+#    #+#             */
// /*   Updated: 2025/08/16 16:54:44 by mlagniez         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int is_ctrl_op(char *rline, int beginning);

// t_line *make_line(char *rline, int len)
// {
// 	t_line *line;

// 	line = malloc(sizeof(t_line));
// 	if (!line)
// 		return (NULL);
// 	line->ctrl_op = is_ctrl_op(rline, 1);
// 	line->raw_line = malloc(sizeof(char) * (len + 1));
// 	if (!line->raw_line)
// 		return (free(line), NULL);
// 	ft_strlcpy(line->raw_line, rline + (line->ctrl_op % 3), len + 1);
// 	printf("line %s\n", line->raw_line);
// 	return (line);
// }

// int is_ctrl_op(char *rline, int beginning)
// {
// 	if (!ft_strncmp(rline, ";", 1) && (beginning || *(rline - 1) != '\\'))
// 		return (SEMICOLON);
// 	else if (!ft_strncmp(rline, "&&", 2) && (beginning || *(rline - 1) != '\\'))
// 		return (AND);
// 	else if (!ft_strncmp(rline, "||", 2) && (beginning || *(rline - 1) != '\\'))
// 		return (OR);
// 	return (0);
// }

// int line_len(char *rline0, char *rline)
// {
// 	int len;
// 	int oper;

// 	len = 0;

// 	(void)rline0;
// 	oper = is_ctrl_op(rline, 1) % 3;
// 	if (oper)
// 	{
// 		rline += oper;
// 		len += oper;
// 		// printf("true\n");
// 	}
// 	while (*rline && !is_ctrl_op(rline, 1))
// 	{
		
// 		rline++;
// 		// printf("%s\n", rline);
// 		if (*rline && *(rline - 1) == '\\')
// 		{
// 			len++;
// 			rline++;
// 		}
// 		len++;
// 	}
// 	// printf("llen : %i\n", len);
// 	return (len);
// }

// int count_lines(char *rline0, char *rline)
// {
// 	int c;

// 	c = 0;

// 	(void)rline0;
// 	while (*rline)
// 	{
// 		// if (line_len(rline, rline))
// 		// 	printf("line_len %i\n", line_len(rline, rline));
// 		rline += line_len(rline, rline);
// 		// printf("%s\n", rline);
// 		c++;
// 	}
// 	return (c);
// }

// t_line **split_and_init_lines(t_ms *ms, char *rline0, char *rline)
// {
// 	int c;
// 	t_line **ret;
// 	t_line **ret0;
// 	int len;
	
// 	(void)ms;
// 	c = count_lines(rline0, rline);
// 	// printf("lines %i\n", c);
// 	ret = malloc(sizeof(t_line *) * (c + 1));
// 	if (!ret)
// 		return (NULL);
// 	while (*rline)
// 	{
// 		len = line_len(rline, rline);
// 		*ret = make_line(rline, len);
// 		if (!*ret++)
// 			return (free(rline0), NULL); //free_lines(ret0) somehow;
// 		rline += len;
// 	}
// 	free(rline0);
// 	return (ret0 = 0, NULL);
// }