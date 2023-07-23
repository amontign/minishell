/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:52:25 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/23 17:03:53 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	builtin_cd(char *dir_name)
{
	char	buf[FILENAME_MAX];

/*Si il y a un pipe avant ou apres une command cd, cd ne s'execute pas.*/
	ft_printf("\n%s\n", getcwd(buf, FILENAME_MAX));
	if (chdir(dir_name) == -1)
	{
		ft_printf("minishell: cd : %s: %s\n", dir_name, strerror(errno));
		return ;
	}
	ft_printf("\n%s\n", getcwd(buf, FILENAME_MAX));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*cat[4];

// 	cat[0] = "cat";
// 	cat[1] = "../../file";
// 	cat[2] = NULL;
// 	cat[3] = NULL;
// 	(void)argc;
// 	// (void)envp;
// 	(void)argv;
// 	// builtin_cd(argv[1]);
// 	if (execve("/bin", cat, envp) == -1)
// 		return (ft_printf("%s\n", strerror(errno)), -1);
// 	return (0);
// }