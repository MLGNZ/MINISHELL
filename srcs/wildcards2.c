/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchevall <tchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:11:57 by tchevall          #+#    #+#             */
/*   Updated: 2025/10/08 17:02:08 by tchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	flags[0] = directory;
	flags[1] = check;
	flags[2] = first_n_last; */

int	ft_strcasecmp(const char *s1, const char *s2)
{
	int		i;
	char	c1;

	c1 = *s1;
	i = 0;
	while (!ft_isalnum(*s1))
		s1++;
	while (!ft_isalnum(*s2))
		s2++;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!(ft_tolower(s1[i]) - ft_tolower(s2[i])))
		return ((-ft_strncmp(s1, s2, ft_strlen(s1))) + c1 == s1[0]);
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]) );
}

void	sort_wild(t_list **lst)
{
	int		sorted;
	t_list	*curr;
	char	*temp;

	if (!lst || !*lst)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = *lst;
		while (curr->next)
		{
			if (ft_strcasecmp(curr->content, curr->next->content) > 0)
			{
				temp = curr->content;
				curr->content = curr->next->content;
				curr->next->content = temp;
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}
int		wildcards_expansion(char **s, t_list **lst)
{
	char	**wild_requ;
	char	**ret_tab;
	int		flags[3];
	t_list *ll;
	t_list	*mf;

	flags[0] = 0;
	flags[1] = 1;
	flags[2] = 0;
	if (s && *s && **s && (*s)[ft_strlen(*s) - 1] == '/')
	{
		(*s)[ft_strlen(*s) - 1] = 0;
		flags[0] = 1;
	}
	wild_requ = get_wild_pattern(s, &flags[2], 0, &flags[1]);
	if (!flags[1])
		return (0);
	mf = matching_files_in_list(wild_requ, flags[2], &flags[1], flags[0]);
	if (!flags[1])
		return (0);
	// lst_print(mf);
	// printf("end\n");
	if (!mf)
	{
		if (flags[0])
			(*s)[ft_strlen(*s)] = '/';
		remove_quotes(*s, *s);
		remove_backslashes(*s, *s);
		mf = ft_lstnew(ft_strdup(*s));//protec
		ft_lstadd_back(lst, mf);
		return (1);
	}
	// free(*s);
	ft_lstadd_back(lst, mf);
	return (1);
}

/*	flags[0] = directory;
	flags[1] = check;
	flags[2] = first_n_last; */
int wildcards_expansion_var(char **s)
{
	char	**wild_requ;
	char	*ret;
	int		flags[3];

	flags[0] = 0;
	flags[1] = 1;
	flags[2] = 0;
	if (s && *s && **s && (*s)[ft_strlen(*s) - 1] == '/')
	{
		(*s)[ft_strlen(*s) - 1] = 0;
		flags[0] = 1;
	}
	wild_requ = get_wild_pattern(s, &flags[2], 0, &flags[1]);
	if (!flags[1])
		return (0);
	ret = matching_files(wild_requ, flags[2], &flags[1], flags[0]);
	if (!flags[1])
		return (0);
	if (!ret)
	{
		if (flags[0])
			(*s)[ft_strlen(*s)] = '/';
		return (1);
	}
	return (free(*s), *s = ret, 1);
}

int	wildcards_in_redir(t_ms *ms, char **s)
{
	char	**wild_requ;
	char	*ret;
	int flags[3];

	flags[0] = 0;
	flags[1] = 1;
	flags[2] = 0;
	if (s && *s && **s && (*s)[ft_strlen(*s) - 1] == '/')
	{
		(*s)[ft_strlen(*s) - 1] = 0;
		flags[0] = 1;
	}
	wild_requ = get_wild_pattern(s, &flags[2], 0, &flags[1]);
	if (!flags[1])
		return (0);
	ret = matching_files(wild_requ, flags[2], &flags[1], flags[0]);
	if (!flags[1])
		return (0);
	if (!ret)
	{
		if (flags[0])
			(*s)[ft_strlen(*s)] = '/';
		return (1);
	}
	if (is_ambiguous(ret))
		return (free(ret), ambiguous_message(*s), 0);
	return (free(*s), *s = ret, 1);
}

int	manage_wildcards(t_ms *ms, char **tab, int type, t_list **lst)
{
	char **wcs;

	if (type == CMD_LT && !wildcards_expansion(tab, lst))
			return (panic(ms, 52), 0);
	if (type == REDIR && !wildcards_in_redir(ms, tab))
		return (0);
	if (type == VAR && !wildcards_expansion_var(tab))
		return (panic(ms, 52), 0);
	return (1);
}

int	iter_wild(char *d_name, char **wild_ptrn, int first_n_last, int i)
{
	while (*d_name && wild_ptrn[i])
	{
		if (*(d_name + 1) && iter_wild(d_name + 1, wild_ptrn, first_n_last, i))
			return (1);
		if (!ft_strncmp(wild_ptrn[i], d_name, ft_strlen(wild_ptrn[i])))
			d_name += ft_strlen(wild_ptrn[i++]);
		else
			d_name++;
	}
	if (wild_ptrn[i])
		return (0);
	if (first_n_last == 2 || first_n_last == 3)
	{
		if (*d_name)
			return (0);
	}
	return (1);
}

int	match_wild_pattern(char *d_name, char **wild_pattern, int first_n_last)
{
	int	i;

	if (!wild_pattern || !d_name || d_name[0] == '.')
		return (0);
	if (!*wild_pattern)
		return (1);
	i = 0;
	if (first_n_last == 1 || first_n_last == 3)
	{
		if (!ft_strncmp(wild_pattern[i], d_name, ft_strlen(wild_pattern[i])))
			d_name += ft_strlen(wild_pattern[i++]);
		else
			return (0);
	}
	if (iter_wild(d_name, wild_pattern, first_n_last, i))
		return (1);
	return (0);
}

char	*wild_join(char *src, char *d_name)
{
	int		size;
	char	*ret;

	ret = NULL;
	size = ft_strlen(src) + ft_strlen(d_name);
	if (src)
	{
		ret = ft_strjoin_free1(src, " ");
		if (!ret)
			return (NULL);
	}
	ret = ft_strjoin_free1(ret, d_name);
	return (ret);
}

// int replace_in_tab(char ***tab_addr, char **tab, char **wcs)
// {
	
// }