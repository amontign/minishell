/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/23 18:06:51 by amontign         ###   ########.fr       */
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
	i = 0;
	while (first)
	{
		env_tab[i] = ft_strdup(first->var);
		if (!env_tab[i])
			return (NULL);
		first = first->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	exit_env(int new, t_data *env)
{
	char	*tmp;
	char	*tmp2;

	while (env)
	{
		if (ft_strncmp(env->var, "?=", 2) == 0)
		{
			free(env->var);
			tmp = ft_itoa(WEXITSTATUS(new));
			tmp2 = ft_strjoin("?=", tmp);
			free(tmp);
			env->var = ft_strdup(tmp2);
			//printf("status : %s\n", tmp);
			free(tmp2);
			break ;
		}
		env = env->next;
	}
}

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

	heredoc_fd = open("heredoc_tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(heredoc_fd, current->heredoc, strlen(current->heredoc) + 1);
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
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		new_fd_out = open(current->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (new_fd_out < 0)
	{
		//error lors de l'ouverture de l'outfile
		exit(1);
	}
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
		dup2(pipefd[1], 1);
	close(pipefd[0]);
}

int	in_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0)
	{
		return (1);
	}
	return (0);
}

int	exec_builtin(char **args, int fd)
{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args, fd);
	if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args);
	/*if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args);
	if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd(args);
	if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args);
	if (ft_strcmp(args[0], "env") == 0)
		builtin_env(args);
	if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args);*/
	return (0);
}

int	execute_child2(t_cmd_tab *cu, t_data *env, t_parsing **l, t_cmd_tab **c)
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
	//free tout
	ft_lstclear_data(&env);
	free_cmd_struct(c);
	ft_lstclear_minishell(l);
	//endof free
	execve(path, args, env_tab);
	//error si on est ici = liberer args et env_tab et path
	exit(EXIT_FAILURE);
}

void	execute_cmds_exit(t_cmd_tab **cmd_struct)
{
	child_process = 0;
	unlink("heredoc_tmp.txt");
	free_cmd_struct(cmd_struct);
}

void	execute_cmds_init_current(int *pipefd, pid_t *pid, t_cmd_tab *current)
{
	if (in_builtin(current->args[0]))
	{
		if (current->next)
		{
			pipe(pipefd);

			int saved_stdout = dup(STDOUT_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);

			exec_builtin(current->args, pipefd[1]);

			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			close(pipefd[1]);
		}
		else
			exec_builtin(current->args, 1);
	}
	else
	{
		pipe(pipefd);
		child_process = 1;
		*pid = fork();
	}
}

void	execute_cmds_parent(pid_t *pid, int *status, t_data *env, int *input_fd)
{
	waitpid(*pid, status, 0);
	exit_env(*status, env);
	if (*input_fd != 0)
		close(*input_fd);
}

int	execute_cmds(t_cmd_tab **c_s, t_cmd_tab *cu, t_data *env, t_parsing **l)
{
	int			pipefd[2];
	int			input_fd;
	int			status;
	pid_t		pid;

	input_fd = 0;
	while (cu)
	{
		execute_cmds_init_current(pipefd, &pid, cu);
		if (pid == 0)
		{
			execute_child1(cu, input_fd, pipefd);
			execute_child2(cu, env, l, c_s);
		}
		else if (pid < 0)
			return (0);
		else
		{
			execute_cmds_parent(&pid, &status, env, &input_fd);
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		cu = cu->next;
	}
	return (execute_cmds_exit(c_s), 1);
}

int	prompt_execution(t_parsing **lexing, t_data *env)
{
	t_cmd_tab	*first;

	first = NULL;
	lexing_to_cmd_tab(*lexing, &first);
	if (!find_place_path(&first, env))
	{
		printf("erreur dans le path\n");
	}
	if (!execute_cmds(&first, first, env, lexing))
	{
		printf("erreur dans l'execution\n");
		return (0);
	}
	//cmd_struct_iter(first, print_node_content);
	return (1);
}
