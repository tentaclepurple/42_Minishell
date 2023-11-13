/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:06:50 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:13 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (*lst != NULL)
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}
