/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/20 15:34:30 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab(t_data *env)
{
	int		i;
	char	**env_tab;
	t_data	*first;

	i = 0;
	first = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	env = first;
	i = 0;
	while (env)
	{
		env_tab[i] = ft_strdup(env->var);
		if (!env_tab[i])
			return (NULL);
		env = env->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	exit_env(int new, t_data *env)
{
	char	*tmp;
	
	while (env)
	{
		if (ft_strncmp(env->var, "?=", 2))
		{
			free(env->var);
			tmp = ft_itoa(new);
			env->var = ft_strdup(ft_strjoin("?=", tmp));
			//printf("exit code : %s\n", env->var);
			free(tmp);
			break ;
		}
		env = env->next;
	}
}

int handle_infile(t_cmd_tab *current) {
	int new_fd_in;
	new_fd_in = open(current->infile, O_RDONLY);
	if (new_fd_in < 0)
	{
		printf("minishell: no such file or directory: %s\n", current->infile);
		exit(1);
	}
	dup2(new_fd_in, 0);
	close(new_fd_in);
	return new_fd_in;
}

int handle_heredoc(t_cmd_tab *current) {
	int heredoc_fd;
	heredoc_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(heredoc_fd, current->heredoc, strlen(current->heredoc) + 1);
	close(heredoc_fd);
	heredoc_fd = open("heredoc_tmp.txt", O_RDONLY);
	dup2(heredoc_fd, 0);
	close(heredoc_fd);
	return heredoc_fd;
}

int handle_outfile(t_cmd_tab *current) {
	int new_fd_out;
	if (current->outfile_delete)
		new_fd_out = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		new_fd_out = open(current->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_fd_out < 0)
	{
		//error lors de l'ouverture de l'outfile
		exit(1);
	}
	dup2(new_fd_out, 1);
	close(new_fd_out);
	return new_fd_out;
}

int execute_child(t_cmd_tab *current, int input_fd, t_data *env, t_parsing **lexing, t_cmd_tab **cmd_struct, int *pipefd) {
	char		**env_tab;
	char		*path;
	char		**args;
	
	child_process = 1;
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
		dup2(pipefd[1], 1);
	close(pipefd[0]);
	env_tab = env_to_tab(env);
	if (!env_tab)
		return (0);
	path = ft_strdup(current->path);
	args = str_tab_dup(current->args);
	//free tout
	ft_lstclear_data(&env);
	free_cmd_struct(cmd_struct);
	ft_lstclear_minishell(lexing);
	(void)lexing;
	//endof free
	execve(path, args, env_tab);
	//error si on est ici = liberer args et env_tab et path
	exit(1);
}

int execute_cmds(t_cmd_tab **cmd_struct, t_data *env, t_parsing **lexing)
{
	t_cmd_tab	*current;
	int			pipefd[2];
	int			input_fd;
	int 		status;
	pid_t		pid;

	current = *cmd_struct;
	input_fd = 0;
	while (current)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			execute_child(current, input_fd, env, lexing, cmd_struct, pipefd);
		else if (pid < 0)
		{
			//error when fork
			return (0);
		}
		else
		{
			waitpid(pid, &status, 0);
			exit_env(status, env);
			if (input_fd != 0)
				close(input_fd);
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		current = current->next;
	}
	unlink("heredoc_tmp.txt");
	free_cmd_struct(cmd_struct);
	return (1);
}

int	prompt_execution(t_parsing **lexing, t_data *env)
{
	t_cmd_tab	*first;

	first = NULL;
	lexing_to_cmd_tab(*lexing, &first);
	if (!find_place_path(&first, env))
	{
		printf("erreur dans le path\n");
		return (0);
	}
	if (!execute_cmds(&first, env, lexing))
	{
		printf("erreur dans l'execution\n");
		return (0);
	}
	//cmd_struct_iter(first, print_node_content);
	return (1);
}
