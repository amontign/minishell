/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:52:25 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/31 12:20:16 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd_env(char *old, char *new, t_data *env)
{
	while (env)
		{
			if (ft_strncmp(env->var, "PWD=", 4) == 0)
			{
				free(env->var);
				env->var = ft_strjoin("PWD=", new);
			}
			else if (ft_strncmp(env->var, "OLDPWD=", 7) == 0)
			{
				free(env->var);
				env->var = ft_strjoin("OLDPWD=", old);
			}
			env = env->next;
		}
}

int	builtin_cd(char **dir_name, t_data *env)
{
	char	old_path[FILENAME_MAX];
	char	new_path[FILENAME_MAX];
	t_data	*env2;

	env2 = env;
	getcwd(old_path, FILENAME_MAX);
	if (!dir_name[1])
	{
		while (env)
		{
			if (ft_strncmp(env->var, "HOME=", 5) == 0)
			{
				chdir(env->var + 5);
				break ;
			}
			env = env->next;
		}
		if (!env)
			ft_printf("minishell: cd : HOME not set\n");
	}
	else if (chdir(dir_name[1]) == -1)
	{
		ft_printf("minishell: cd : %s: %s\n", dir_name[1], strerror(errno));
		return (1);
	}
	getcwd(new_path, FILENAME_MAX);
	change_pwd_env(old_path, new_path, env2);
	return (0);
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