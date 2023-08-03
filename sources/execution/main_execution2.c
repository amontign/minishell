/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:43:06 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:46:30 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	e_c_i_c2(t_norm_exec *normy, t_cmd_tab *c, t_data **env)
{
	int	saved_stdout;

	pipe(normy->pipefd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(normy->pipefd[1], STDOUT_FILENO);
	exec_builtin(c->args, normy, env, c);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	close(normy->pipefd[1]);
}

int	execute_cmds_exit(t_cmd_tab **cmd_struct, t_norm_exec *normy)
{
	g_child_process = 0;
	unlink("heredoc_tmp.txt");
	free_cmd_struct(cmd_struct);
	if (normy->exit != 257)
		return (normy->exit % 256);
	return (257);
}

char	*last_command(t_cmd_tab **cmd_struct)
{
	t_cmd_tab	*current;

	current = *cmd_struct;
	while (current && current->next)
	{
		current = current->next;
	}
	if (current)
		return (current->cmd_name);
	return (NULL);
}

t_cmd_tab	*last_command_struct(t_cmd_tab **cmd_struct)
{
	t_cmd_tab	*current;

	current = *cmd_struct;
	while (current && current->next)
	{
		current = current->next;
	}
	if (current)
		return (current);
	return (NULL);
}

void	exit_env(t_norm_exec *normy, t_data *env, t_cmd_tab **cmd_struct)
{
	int			i;

	i = -1;
	while (++i < normy->num_cmds)
		waitpid(normy->pids[i], &(normy->status), 0);
	free(normy->pids);
	if (!in_builtin(last_command(cmd_struct))
		&& last_command_struct(cmd_struct)->exec != 0)
	{
		if (WIFEXITED(normy->status))
			change_status(env, WEXITSTATUS(normy->status));
		if (WIFSIGNALED(normy->status))
			change_status(env, WTERMSIG(normy->status) + 128);
	}
}
