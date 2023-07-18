/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/15 22:13:46 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_cmds(t_cmd_tab **cmd_struct, t_data *env)
{
	t_cmd_tab	*current = *cmd_struct;
	int			pipefd[2];
	int			input_fd;
	int			new_fd_in;
	int			new_fd_out;
	pid_t		pid;
	(void)env;

	input_fd = 0;
	while (current)
	{
		pipe(pipefd);

		pid = fork();
		if (pid == 0)
		{
			if (current->infile)
			{
				new_fd_in = open(current->infile, O_RDONLY);
				if (new_fd_in < 0)
				{
					//error
					exit(1);
				}
				dup2(new_fd_in, 0);
				close(new_fd_in);
			}
			else if (input_fd)
			{
				dup2(input_fd, 0);
				close(input_fd);
			}
			if (current->outfile)
			{
				new_fd_out = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (new_fd_out < 0)
				{
					//error
					exit(1);
				}
				dup2(new_fd_out, 1);
				close(new_fd_out);
			}
			else if (current->next)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			//free tout avant ce point
			execve(current->path, current->args, NULL);
			//error si on est ici
			exit(1);
		}
		else if (pid < 0)
		{
			//error when fork
			return (0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (input_fd != 0)
				close(input_fd);
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		current = current->next;
	}
	return (1);
}

int	prompt_execution(t_parsing **lexing, t_data *env)
{
	t_cmd_tab	*first;

	first = NULL;
	lexing_to_cmd_tab(*lexing, &first);
	if (!find_place_path(&first, env))
	{
		printf("erreur dans l'execution\n");
		return (0);
	}
	if (!execute_cmds(&first, env))
	{
		printf("erreur dans l'execution\n");
		return (0);
	}
	//cmd_struct_iter(first, print_node_content);
	return (1);
}
