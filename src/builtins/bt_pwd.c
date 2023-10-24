/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:00:14 by imontero          #+#    #+#             */
/*   Updated: 2023/10/24 18:14:07 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

int main() 
{
    char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("PWD ERROR");
	ft_putendl_fd(cwd, 1);
	free(cwd);
}
