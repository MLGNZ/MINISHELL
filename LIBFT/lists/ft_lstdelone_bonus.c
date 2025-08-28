/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:09:27 by mlagniez          #+#    #+#             */
/*   Updated: 2025/05/07 16:12:22 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//void	dele(void *content);

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del((*lst).content);
	free(lst);
}

// void	dele(void *content)
// {
// 	free(content);
// }

// #include <stdio.h>

// int	main()
// {
// 	t_list	*one;
// 	t_list	*two;
// 	t_list	*three;
// 	t_list	**lst;

// 	three = ft_lstnew(ft_strdup("3"));
// 	two = ft_lstnew(ft_strdup("2"));
// 	one = ft_lstnew(ft_strdup("1"));
// 	lst = &one;
// 	ft_lstadd_back(lst, two);
// 	ft_lstadd_back(lst, three);
// 	if (one)
// 		printf("b1: %s\n", (char *)(*one).content);
// 	if (two)
// 		printf("b2: %s\n", (char *)(*two).content);
// 	if (three)
// 		printf("b3: %s\n", (char *)(*three).content);
// 	ft_lstdelone(two, dele);
// 	if (one)
// 		printf("a1: %s\n", (char *)(*one).content);
// 	if (two)
// 		printf("a2: %s\n", (char *)(*two).content);
// 	if (three)
// 		printf("a3: %s\n", (char *)(*three).content);
// 	return (0);
// }