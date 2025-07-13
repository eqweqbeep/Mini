/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:46:23 by jait-chd          #+#    #+#             */
/*   Updated: 2025/07/13 21:46:24 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(1, cwd, strlen(cwd));
		write(1, "\n", 1);
		// exit(0);
	}
	else
		perror("pwd");
	return (0);
}
 // pwd + arg must ignore all options next to pwd and affiche pwd

 // mkdir test and remove it on another terminal and test pwd
//  mkdir test_dir
// cd test_dir
// chmod 000 .
// pwd
// # Should still work (pwd doesn't need read permission)
// some test cases with symbolic links
//13. PWD in Pipelines
//14. PWD with Redirections
//15. PWD in Subshells
//16. PWD in Command Substitution
//18. PWD When $PWD is Modified
// 19. PWD When $PWD is Unset
