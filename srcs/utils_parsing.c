/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:27:34 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 20:53:14 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_cmd(char**tab, t_ms *ms)
{
	char	*cmd_file;

	cmd_file = NULL;
	if (!tab)
		return (1);
	if (is_build_in(*tab))
		return (1);
	if (*tab && **tab == '/')
		return (puts("true"), 1);
	if (!find_file(*tab, &cmd_file, ft_getenv("PATH", ms)))
		return (0);
	if (!cmd_file)
		return (1);
	free(*tab);
	*tab = cmd_file;
	return (1);
}

void	offset_array(char ***tab_p)
{
	char	**tab;
	int		i;

	tab = *tab_p;
	i = -1;
	while (tab && tab[++i])
		tab[i] = tab[i + 1];
	if (!tab[0])
	{
		free(tab);
		tab = NULL;
	}	
	*tab_p = tab;
}

int	is_build_in(char *str)
{
	if (!ft_strncmp(str, "echo", 5) || \
		!ft_strncmp(str, "cd", 3) || \
		!ft_strncmp(str, "pwd", 4) || \
		!ft_strncmp(str, "export", 7) || \
		!ft_strncmp(str, "unset", 6) || \
		!ft_strncmp(str, "env", 4) || \
		!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

char	*ft_getenv(char *key, t_ms *ms)
{
	t_list	*env;
	int		key_len;

	key_len = ft_strlen(key);
	env = ms->lst_env;
	while (env)
	{
		if (!ft_strncmp(env->content, key, key_len) && \
		ft_strlen(env->content) > (size_t)key_len && ((char *)env->content)[key_len] == '=')
			return (&(((char *)env->content)[key_len + 1]));
		env = env->next;
	}
	return (0);
}
