/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:44:31 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	e_c_i_c(t_norm_exec *normy, pid_t *pid, t_cmd_tab *c, t_data **env)
{
	if (in_builtin(c->args[0]))
	{
		if (!c->next)
		{
			normy->output = 1;
			exec_builtin(c->args, normy, env, c);
		}
		else
			e_c_i_c2(normy, c, env);
	}
	else
	{
		pipe(normy->pipefd);
		g_child_process = 1;
		*pid = fork();
	}
}

void	execute_cmds_parent(t_norm_exec *normy, t_cmd_tab *cu)
{
	if (normy->input_fd != 0)
		close(normy->input_fd);
	normy->input_fd = (!in_builtin(cu->cmd_name) && close(normy->pipefd[1]));
	normy->input_fd = normy->pipefd[0];
}

void	execute_cmds_no_exec(t_norm_exec *normy)
{
	if (normy->input_fd)
		close(normy->input_fd);
	normy->input_fd = open("/dev/null", O_RDONLY);
}

int	execute_cmds(t_cmd_tab **c_s, t_cmd_tab *cu, t_data **env, t_parsing **l)
{
	t_norm_exec	normy;

	init_exec(&normy, c_s);
	while (cu)
	{
		if (cu->exec)
		{
			e_c_i_c(&normy, &normy.pids[normy.num_cmds], cu, env);
			if (normy.pids[normy.num_cmds] == 0 && !in_builtin(cu->cmd_name))
			{
				execute_child1(cu, normy.input_fd, normy.pipefd);
				e_c2(cu, *env, l, c_s);
			}
			else if (normy.pids[normy.num_cmds] < 0)
				return (0);
			else
				execute_cmds_parent(&normy, cu);
			normy.num_cmds++;
		}
		else
			execute_cmds_no_exec(&normy);
		cu = cu->next;
	}
	exit_env(&normy, *env, c_s);
	return (execute_cmds_exit(c_s, &normy));
}

int	prompt_execution(t_parsing **lexing, t_data **env)
{
	t_cmd_tab	*first;

	first = NULL;
	lexing_to_cmd_tab(*lexing, &first, *env);
	find_place_path(&first, *env);
	return (execute_cmds(&first, first, env, lexing));
}
