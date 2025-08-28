/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagniez <mlagniez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:52:53 by mlagniez          #+#    #+#             */
/*   Updated: 2025/08/26 15:54:22 by mlagniez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	(*new).content = content;
	(*new).next = 0;
	return (new);
}

// #include <stdio.h>
//
// int main()
// {
// 	t_list *test;
//
// 	test = ft_lstnew("yes");
// 	printf("%s\n", (char *)test->content);
// 	return (0);
// }