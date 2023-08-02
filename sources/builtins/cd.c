/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:52:25 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 18:05:45 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd_env(char *new, t_data *env)
{
	t_data	*old_env;
	char	*old_env_char;

	old_env_char = NULL;
	old_env = env;
	while (old_env)
	{
		if (ft_strncmp(old_env->var, "PWD=", 4) == 0)
		{
			old_env_char = ft_strdup(old_env->var + 4);
			free(old_env->var);
			old_env->var = ft_strjoin("PWD=", new);
			break ;
		}
		old_env = old_env->next;
	}
	while (env)
	{
		if (ft_strncmp(env->var, "OLDPWD=", 7) == 0)
		{
			if (old_env_char)
			{
				free(env->var);
				env->var = ft_strjoin("OLDPWD=", old_env_char);
			}
			break ;
		}
		env = env->next;
	}
	if (old_env_char)
		free(old_env_char);
}

int	builtin_cd(char **dir_name, t_data *env, t_cmd_tab *current)
{
	char	new_path[FILENAME_MAX];
	t_data	*env2;

	env2 = env;
	if (dir_name[1] && dir_name[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else if (!command_only_e(current))
	{
		return (0);
	}
	else if (!dir_name[1])
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
		{
			ft_printf("minishell: cd : HOME not set\n");
			return (1);
		}
	}
	else if (chdir(dir_name[1]) == -1)
	{
		ft_printf("minishell: cd : %s: %s\n", dir_name[1], strerror(errno));
		return (1);
	}
	getcwd(new_path, FILENAME_MAX);
	change_pwd_env(new_path, env2);
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
