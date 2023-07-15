/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:35:26 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/11 16:01:59 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_not_command(char *cmd, char **argv)
{
	int	i;
	int	size_cmd;

	i = 0;
	size_cmd = ft_strlen(cmd);
	while (i < size_cmd && cmd[i] == ' ' && cmd[i])
		i++;
	if (i < size_cmd && cmd[i] == '|')
		return (TRUE);
	if (i < size_cmd && (cmd[i] == '<' || cmd[i] == '>') && argv[3][0] == '|')
		return (TRUE);
	return (FALSE);
}

void	exec_single_cmd(char **cmd, char **argv, char **envp)
{
	char	*path;

	if (check_for_backslash(argv[2]) == TRUE)
	{
		if (access(cmd[0], F_OK | X_OK) == -1)
			ft_printf("pipex: %s: %s\n", argv[2], strerror(errno));
		// if (is_builtin() == TRUE)
		// 	exec_builtin();
		// else
		if (execve(cmd[0], cmd, envp) == -1)
			ft_printf("%s\n", strerror(errno));
	}
	else
	{
		// if (is_builtin() == TRUE)
		// 	exec_builtin();
		// else
		// {
			path = find_path(cmd[0], envp);
			if (!path)
				ft_printf("%s: command not found\n", cmd[0]);
			if (execve(path, cmd, envp) == -1)
				ft_printf("%s\n", strerror(errno));
		// }
	}
}
