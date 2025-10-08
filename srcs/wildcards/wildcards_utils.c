/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:58:05 by mlagniez          #+#    #+#             */
/*   Updated: 2025/10/08 19:25:55 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
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

void	put_back_slash_at_the_end_if_necessary(char **str_ptr, int is_dir)
{
	if (is_dir)
			(*str_ptr)[ft_strlen(*str_ptr)] = '/';
}

int	handle_no_match(t_list **mf, char **s, int is_dir)
{
	char	*new;

	if (*mf)
		return (1);
	put_back_slash_at_the_end_if_necessary(s, is_dir);
	remove_quotes(*s, *s);
	remove_backslashes(*s, *s);
	new = ft_strdup(*s);
	*mf = ft_lstnew(new);
	if (!new || !*mf)
		return (ft_lstclear(mf, free), 0);
	return (1);
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
