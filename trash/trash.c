/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:25:27 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/14 17:27:13 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*Everything I've made but won't make it to the final cut*/

static int	cw_ev(const char *s, char c)
{
	char	*s1;
	int		nw;

	nw = 0;
	s1 = (char *)s;
	while (*s1)
	{
		if ((*s1 != c && s == s1) || (*s1 != c && *(s1 - 1) == c))
			nw++;
		s1++;
	}
	return (nw);
}

char **split_everything(char **tb)
{
	int len;

	len = 0;
	while (tb && *tb)
	{
		if (which_op(*tb) || **tb == '\'' || **tb == '\"')
			len++;
		else
			len += cw_ev(*tb, ' ');
		tb++;
	}
	// char **ret;
	// ret = malloc(size_of)
	return (0);
}

int is_arg(char **tb, char **tb1)
{
	int op;
	// static int in_com;
	int ret;

	ret = 0;
	op = which_op(*tb1);
	if (op == PIPE || op == EOL)
	{
		// in_com = 0;
		ret--;
	}
	else if (op && op != PIPE && !which_op(*(tb1 + 1)) && *(tb1 + 1))
	{
		// in_com = 0;
		ret--;
	}
	/*if 
	not an op
	first
	if a pipe is before
	if a non-op before and a op thats not a pipe before*/
	else if (!op &&
		(tb1 == tb || 
			which_op((*(tb1 - 1))) == PIPE ||
				((tb1 - tb > 1) && !which_op((*(tb1 - 1))) && which_op((*(tb1 - 2))) > 2)))
	{
		// in_com = 1;
		ret++;
	}
	// if (!*(++tb1))
	// 	in_com = 0;
	return (ret);
}

int counting_args(char **tb)
{
	char **tb1;
	int c;
	int in_com;

	in_com = 0;
	c = 0;
	tb1 = tb;
	while (tb1 && *tb1)
	{
		in_com = is_arg(tb, tb1);
		if (in_com)
			c++;
		tb1++;
	}
	return (c);
}

char **make_sub_s(char **beginning, char **src)
{
	char **src1;
	int len;
	// int is_com;

	src1 = src;
	// puts(*src1);
	src1++;
	while (*src1 && !is_arg(beginning, src1))
		src1++;
	len = src1 - src;
	// printf("length = %i\n", len);
	char **ret;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (puts("something terrible happened !"), NULL);
	src1 = src;
	// *ret++ = *src1++;
	// puts("x");
	*(ret + len) = 0;
	while (len--)
		ret[len] = src1[len];
	// while (*src1 && !is_arg(beginning, src1) && puts("x"))
	// 	*ret++ = *src1++;
	// *ret = 0;
	// puts(*ret);
	return (ret);
}

int make_sub_split(char **src, char ***s_s)
{
	char **src1;
	int in_com;

	in_com = 0;
	src1 = src;
	while (src1 && *src1)
	{
		in_com = is_arg(src, src1);
		if (in_com)
		{
			*s_s = make_sub_s(src, src1);
			s_s++;
		}	
		src1++;
	}
	*s_s = NULL;
	return (1);
}

void printss(char ***ss)
{
	while (*ss)
	{
		while (**ss)
		{
			printf("[%s] ",**ss);
			*ss += 1;
		}
		printf("\n");
		ss++; 
	}
}

char ***join_what_needs_to(char **tb)
{
	// (void)temp;
	char ***s_splited;
	int n_args = counting_args(tb);
	printf("%i\n", n_args);
	s_splited = malloc(sizeof(char **) * (n_args + 1));
	make_sub_split(tb, s_splited);
	printss(s_splited);
	return (s_splited = NULL, NULL);
}