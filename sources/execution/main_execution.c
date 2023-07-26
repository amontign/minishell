/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/26 16:19:18 by amontign         ###   ########.fr       */
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

void	exit_env(pid_t *pids, int num_cmds, int new, t_data *env)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &new, 0);
		i++;
	}
	free(pids);
	while (env)
	{
		if (ft_strncmp(env->var, "?=", 2) == 0)
		{
			free(env->var);
			tmp = ft_itoa(WEXITSTATUS(new));
			tmp2 = ft_strjoin("?=", tmp);
			free(tmp);
			env->var = ft_strdup(tmp2);
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
	{
		dup2(pipefd[1], 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
}

int	in_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0)
	{
		return (1);
	}
	return (0);
}

int	exec_builtin(char **args, int fd, t_data *env, t_cmd_tab *current)
{
	if (current->outfile)
		fd = handle_outfile(current);
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args, fd);
	if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, env);
	/*if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args);*/
	if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd(args, fd);
	if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args, env, fd);
	if (ft_strcmp(args[0], "env") == 0)
		builtin_env(args, env, fd);
	if (current->outfile)
	{
		dup2(1, fd);
		close(fd);
	}
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

void	e_c_i_c(int *pipefd, pid_t *pid, t_cmd_tab *current, t_data *env)
{
	int	saved_stdout;

	if (in_builtin(current->args[0]))
	{
		if (current->next)
		{
			pipe(pipefd);
			saved_stdout = dup(STDOUT_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			exec_builtin(current->args, pipefd[1], env, current);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			close(pipefd[1]);
		}
		else
			exec_builtin(current->args, 1, env, current);
	}
	else
	{
		pipe(pipefd);
		child_process = 1;
		*pid = fork();
	}
}

void	execute_cmds_parent(int *input_fd)
{
	if (*input_fd != 0)
		close(*input_fd);
}

int	count_cmds(t_cmd_tab *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	init_exec(t_norm_exec *normy)
{
	normy->num_cmds = 0;
	normy->input_fd = 0;
	normy->status = 0; //supprimer quand le retour des builtin sera gere
}

int	execute_cmds(t_cmd_tab **c_s, t_cmd_tab *cu, t_data *env, t_parsing **l)
{
	t_norm_exec	normy;

	init_exec(&normy);
	normy.pids = ft_calloc(sizeof(pid_t), count_cmds(*c_s));
	while (cu)
	{
		e_c_i_c(normy.pipefd, &normy.pids[normy.num_cmds], cu, env);
		if (normy.pids[normy.num_cmds] == 0 && !in_builtin(cu->cmd_name))
		{
			execute_child1(cu, normy.input_fd, normy.pipefd);
			execute_child2(cu, env, l, c_s);
		}
		else if (normy.pids[normy.num_cmds] < 0)
			return (0);
		else
		{
			execute_cmds_parent(&normy.input_fd);
			close(normy.pipefd[1]);
			normy.input_fd = normy.pipefd[0];
		}
		cu = cu->next;
		normy.num_cmds++;
	}
	exit_env(normy.pids, normy.num_cmds, normy.status, env);
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
