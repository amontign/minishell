/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:37:47 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:42:11 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_outfile_builtin(t_cmd_tab *current)
{
	int	new_fd_out;

	if (current->outfile_delete)
		new_fd_out = open(current->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		new_fd_out = open(current->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_fd_out < 0)
		exit(1);
	return (new_fd_out);
}

void	exec_builtin2(char **args, int *status, t_cmd_tab *c, t_data **env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		*status = builtin_cd(args, *env, c);
	if (ft_strcmp(args[0], "unset") == 0)
		*status = unset(env, args, c);
}

int	exec_builtin(char **a, t_norm_exec *n, t_data **env, t_cmd_tab *c)
{
	int	status;
	int	fd;

	fd = n->pipefd[1];
	if (n->output)
		fd = 1;
	if (c->outfile)
		fd = handle_outfile_builtin(c);
	if (ft_strcmp(a[0], "echo") == 0)
		status = builtin_echo(a, fd);
	if (ft_strcmp(a[0], "pwd") == 0)
		status = builtin_pwd(a, fd);
	if (ft_strcmp(a[0], "export") == 0)
		status = export(a, *env, fd, c);
	if (ft_strcmp(a[0], "env") == 0)
		status = builtin_env(a, *env, fd);
	if (ft_strcmp(a[0], "exit") == 0)
		status = builtin_exit(a, n, c);
	exec_builtin2(a, &status, c, env);
	if (c->outfile)
		close(fd);
	n->output = 0;
	if (in_builtin(last_command(&c)))
		change_status(*env, status);
	return (0);
}
