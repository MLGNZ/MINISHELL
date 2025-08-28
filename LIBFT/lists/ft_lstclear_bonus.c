/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:28:59 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 19:26:06 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
	if (*lst)
	{
		ft_lstdelone(*lst, del);
	}		
}

// void	dele(void *content)
// {
// 	free(content);
// }
//
// #include <stdio.h>
//
// int	main()
// {
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	**lst;
//
// 	three = ft_lstnew(ft_strdup("3"));
// 	two = ft_lstnew(ft_strdup("2"));
// 	one = ft_lstnew(ft_strdup("1"));
// 	lst = &one;
// 	ft_lstadd_back(lst, two);
// 	ft_lstadd_back(lst, three);
// 	printf("b1: %s\n", (char *)(*one).content);
// 	printf("b2: %s\n", (char *)(*two).content);
// 	printf("b3: %s\n", (char *)(*three).content);
// 	ft_lstclear(lst, dele);
// 	printf("a1: %s\n", (char *)(*one).content);
// 	printf("a2: %s\n", (char *)(*two).content);
// 	printf("a3: %s\n", (char *)(*three).content);
// 	return (0);
// }