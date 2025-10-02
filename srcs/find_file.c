/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:28:32 by mlagniez          #+#    #+#             */
/*   Updated: 2025/09/26 17:32:59 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_of_path(char *path);

int	file_for_no_path(char *cmd_test, char **file_address)
{
	char	*cmd_test2;

	cmd_test2 = ft_strn1join(".", cmd_test, 1);
	if (!cmd_test2)
		return (free(cmd_test), 0);
	if (!access(cmd_test2, X_OK))
		return (free(cmd_test), *file_address = cmd_test2, 1);
	free(cmd_test2);
	return (1);
}

int	find_file(char *cmd, char **file_address, char *path, int i)
{
	char	*cmd_test2;
	char	*cmd_test;

	cmd_test = ft_strjoin("/", cmd);
	if (!cmd_test)
		return (0);
	if (!path)
		return (file_for_no_path(cmd_test, file_address));
	while (path && ++i > -1)
	{
		if (!len_of_path(&(path[i])))
			cmd_test2 = ft_strn1join(".", cmd_test, 1);
		else
			cmd_test2 = ft_strn1join(&(path[i]), cmd_test, \
			len_of_path(&(path[i])));
		if (!cmd_test2)
			return (free(cmd_test), 0);
		if (!access(cmd_test2, X_OK))
			return (free(cmd_test), *file_address = cmd_test2, 1);
		free(cmd_test2);
		i += len_of_path(&(path[i]));
		if (!path || path[i] != ':')
			break ;
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
