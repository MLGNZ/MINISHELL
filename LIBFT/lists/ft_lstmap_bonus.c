/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:04:04 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:12:36 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

// void	free_list(t_list *lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstret;
	t_list	*lstret2;

	lstret = NULL;
	lstret2 = lstret;
	while (lst)
	{
		lstret2 = ft_lstnew((*lst).content);
		if (lstret2 == 0)
		{
			ft_lstclear(&lstret, del);
			return (NULL);
		}
		(*lstret2).content = f((*lstret2).content);
		ft_lstadd_back(&lstret, lstret2);
		lst = (*lst).next;
	}
	return (lstret);
}

// void	*uppper(void *content)
// {
// 	if ((*(char *)content) >= 'a' && (*(char *)content) <= 'z')
// 		*(char *)content -= 32;
// 	return (content);
// }
//
// void	dele(void *content)
// {
// 	free(content);
// }
//
// int	main()
// {
// 	t_list	*begin;
// 	t_list	*a;
// 	t_list	*b;
// 	t_list	*c;
// 	t_list	*new;

// 	begin = NULL;
// 	a = ft_lstnew(ft_strdup("aa"));
// 	b = ft_lstnew(ft_strdup("bb"));
// 	c = ft_lstnew(ft_strdup("cc"));
// 	ft_lstadd_back(&begin, a);
// 	ft_lstadd_back(&begin, b);
// 	ft_lstadd_back(&begin, c);
//
// 	new = ft_lstmap(begin, uppper, dele);
//
// 	while (new)
// 	{
// 		printf("%s\n", (char *)(*new).content);
// 		new = (*new).next;
// 	}
// 	return (0);
// }