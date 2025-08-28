/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:28:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 13:39:02 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_of_path(char *path);

int	find_file(char *cmd, char **file_address, char *path)
{
	char	*cmd_test2;
	int		i;
	char	*cmd_test;

	if (!path)
		return (1);
	cmd_test = ft_strjoin("/", cmd);
	if (!cmd_test)
		return (0);
	i = -1;
	while (path && path[++i])
	{
		if (path[i] == '/' && (!i || path[i - 1] == ':'))
		{
			cmd_test2 = ft_strn1join(&(path[i]), \
				cmd_test, len_of_path(&(path[i])));
			if (!cmd_test2)
				return (free(cmd_test), 0);
			if (!access(cmd_test2, X_OK))
				return (free(cmd_test), *file_address = cmd_test2, 1);
			free(cmd_test2);
		}
	}
	return (free(cmd_test), *file_address = NULL, 1);
}

static int	len_of_path(char *path)
{
	int	len;

	len = 0;
	while (path && *path && *path != ':')
	{
		len++;
		path++;
	}
	return (len);
}
