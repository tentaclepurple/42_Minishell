/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:09:31 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:29 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

t_list	*ft_lstlast(t_list	*lst)
{
	t_list	*node;

	node = lst;
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
	{
		node = node->next;
	}
	return (node);
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
	printf("Content_end: %i\nPointer_end: %p\n", *(int*)ft_lstlast(*lst)->content,\
	 ft_lstlast(*lst)->next);
	node = ft_lstnew(&b);
	ft_lstadd_front(lst, node);
	printf("Content_1: %i\nPointer_1: %p\n", *(int*)(*lst)->content, (*lst)->next);
	printf("Content_end: %i\nPointer_end: %p\n", *(int*)ft_lstlast(*lst)->content,\
	 ft_lstlast(*lst)->next);
	free(node);
	free(lst);
	return (0);
}*/