/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_split_just_replace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:10:30 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/29 03:02:02 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*The purpose of this function is to update an array of string containing
variables. it will take two arrays of string as parameters
and append the second to the first
However, if a key from the second already exists in the first, it will
replace it if it doesn't exist, it will simply be added at the end.*/
static int	key_len_of(char *s)
{
	int	len;

	len = 0;
	while (s && *(s++) && ++len)
	{
		if (*s == '=')
			break ;
	}
	return (len);
}

static char	*is_already_in(char **splt, char *s)
{
	while (splt && *(splt))
	{
		if (!ft_strncmp(*splt, s, key_len_of(s)))
			return (*splt);
		splt++;
	}
	return (0);
}

int	update_split_just_replace(char **splt1, char **splt2)
{
	int		i;
	char	*replace;
	char	*temp;

	i = -1;
	while (splt1 && splt1[++i])
	{
		replace = is_already_in(splt2, splt1[i]);
		if (replace)
		{
			temp = ft_strdup(replace);
			if (!temp)
				return (0);
			free(splt1[i]);
			splt1[i] = temp;
		}
	}
	return (1);
}
