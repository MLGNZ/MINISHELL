/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:12:18 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/03 19:25:35 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	while (lst && (lst)->next)
	{
		temp = lst;
		lst = (lst)->next;
		f((*temp).content);
	}
	if (lst)
	{
		f((*lst).content);
	}
}

// void	uppper(void *content)
// {
// 	if ((*(char *)content) >= 'a' && (*(char *)content) <= 'z')
// 		*(char *)content -= 32;
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

// 	three = ft_lstnew(ft_strdup("c"));
// 	two = ft_lstnew(ft_strdup("b"));
// 	one = ft_lstnew(ft_strdup("a"));
// 	lst = &one;
// 	ft_lstadd_back(lst, two);
// 	ft_lstadd_back(lst, three);
// 	printf("b1: %s\n", (char *)(*one).content);
// 	printf("b2: %s\n", (char *)(*two).content);
// 	printf("b3: %s\n", (char *)(*three).content);
// 	ft_lstiter(one, uppper);
// 	printf("a1: %s\n", (char *)(*one).content);
// 	printf("a2: %s\n", (char *)(*two).content);
// 	printf("a3: %s\n", (char *)(*three).content);
// 	return (0);
// }