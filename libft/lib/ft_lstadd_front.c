/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:08:32 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:17 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include<stdio.h>
int	main(void)
{
	int		a;
	int		b;
	t_list	*node;
	t_list	**lst;

	lst = malloc(sizeof(node));
	a = 42;
	b = 24;
	node = ft_lstnew(&a);
	*lst = NULL;
	ft_lstadd_front(lst, node);
	printf("Content_1: %i\nPointer_1: %p\n", *(int*)(*lst)->content, (*lst)->next);
	node = ft_lstnew(&b);
	ft_lstadd_front(lst, node);
	printf("Content_1: %i\nPointer_1: %p\n", *(int*)(*lst)->content, (*lst)->next);
	printf("Content_2: %i\nPointer_2: %p\n", *(int*)((*lst)->next)->content, \
	((*lst)->next)->next);
	free(node);
	free(lst);
	return (0);
}*/