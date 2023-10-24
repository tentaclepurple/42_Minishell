/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:00:14 by imontero          #+#    #+#             */
/*   Updated: 2023/10/19 17:51:40 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

/*void	ft_pwd(t_px *px)
{
 	char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("PWD ERROR");
	ft_putendl_fd(cwd, 1);
	free(cwd);
}*/

/*void	ft_pwd(t_px *px)
{
    char cwd[5120];

    if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else 
	{
        perror("getcwd");
        return 1;
    }
    return 0;
}*/

/*int main() 
{
    char cwd[5120];

    if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else 
	{
        perror("getcwd");
        return 1;
    }
    return 0;
}*/

int main() 
{
    char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("PWD ERROR");
	ft_putendl_fd(cwd, 1);
	free(cwd);
}
