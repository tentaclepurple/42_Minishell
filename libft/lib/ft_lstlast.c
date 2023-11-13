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

#include "../libft.h"

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
