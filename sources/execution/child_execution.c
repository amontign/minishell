/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:32:59 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:40:22 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_infile(t_cmd_tab *current)
{
	int	new_fd_in;

	new_fd_in = open(current->infile, O_RDONLY);
	if (new_fd_in < 0)
	{
		printf("minishell: no such file or directory: %s\n", current->infile);
		exit(1);
	}
	dup2(new_fd_in, 0);
	close(new_fd_in);
	return (new_fd_in);
}

int	handle_heredoc(t_cmd_tab *current)
{
	int	heredoc_fd;

	heredoc_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(heredoc_fd, current->heredoc, strlen(current->heredoc));
	close(heredoc_fd);
	heredoc_fd = open("heredoc_tmp.txt", O_RDONLY);
	dup2(heredoc_fd, 0);
	close(heredoc_fd);
	return (heredoc_fd);
}

int	handle_outfile(t_cmd_tab *current)
{
	int	new_fd_out;

	if (current->outfile_delete)
		new_fd_out = open(current->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		new_fd_out = open(current->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (new_fd_out < 0)
		exit(1);
	dup2(new_fd_out, 1);
	close(new_fd_out);
	return (new_fd_out);
}

void	execute_child1(t_cmd_tab *current, int input_fd, int *pipefd)
{
	if (current->infile)
		handle_infile(current);
	else if (current->heredoc)
		handle_heredoc(current);
	else if (input_fd)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (current->outfile)
		handle_outfile(current);
	else if (current->next)
	{
		dup2(pipefd[1], 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

int	e_c2(t_cmd_tab *cu, t_data *env, t_parsing **l, t_cmd_tab **c)
{
	char		**env_tab;
	char		*path;
	char		**args;

	env_tab = env_to_tab(env);
	if (!env_tab)
		return (0);
	if (cu->path)
		path = ft_strdup(cu->path);
	else
		path = NULL;
	args = str_tab_dup(cu->args);
	ft_lstclear_data(&env);
	free_cmd_struct(c);
	ft_lstclear_minishell(l);
	execve(path, args, env_tab);
	free_char_tab(args);
	free_char_tab(env_tab);
	free(path);
	exit(EXIT_FAILURE);
}
