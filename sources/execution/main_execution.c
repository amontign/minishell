/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:57:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/30 15:00:22 by amontign         ###   ########.fr       */
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

void	change_status(t_data *env, int status)
{
	char		*tmp;
	char		*tmp2;

	while (env)
	{
		if (ft_strncmp(env->var, "?=", 2) == 0)
		{
			free(env->var);
			tmp = ft_itoa(status);
			tmp2 = ft_strjoin("?=", tmp);
			free(tmp);
			env->var = ft_strdup(tmp2);
			free(tmp2);
			break ;
		}
		env = env->next;
	}
}

void	exit_env(t_norm_exec *normy, t_data *env, t_cmd_tab **cmd_struct)
{
	int			i;

	i = -1;
	while (++i < normy->num_cmds)
		waitpid(normy->pids[i], &(normy->status), 0);
	free(normy->pids);
	if (!in_builtin(last_command(cmd_struct)))
	{
		change_status(env, WEXITSTATUS(normy->status));
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
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0)
	{
		return (1);
	}
	return (0);
}

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
	{
		//error lors de l'ouverture de l'outfile
		exit(1);
	}
	return (new_fd_out);
}

int	exec_builtin(char **args, t_norm_exec *normy, t_data **env, t_cmd_tab *current)
{
	int	status;
	int	fd;

	fd = normy->pipefd[1];
	if (normy->output)
		fd = 1;
	if (current->outfile)
		fd = handle_outfile_builtin(current);
	if (ft_strcmp(args[0], "echo") == 0)
		status = builtin_echo(args, fd);
	if (ft_strcmp(args[0], "cd") == 0)
		status = builtin_cd(args, *env);
	if (ft_strcmp(args[0], "unset") == 0)
		status = builtin_unset(env, args, current);
	if (ft_strcmp(args[0], "pwd") == 0)
		status = builtin_pwd(args, fd);
	if (ft_strcmp(args[0], "export") == 0)
		status = builtin_export(args, *env, fd, current);
	if (ft_strcmp(args[0], "env") == 0)
		status = builtin_env(args, *env, fd);
	if (ft_strcmp(args[0], "exit") == 0)
		status = builtin_exit(args, normy, current);
	if (current->outfile)
		close(fd);
	normy->output = 0;
	change_status(*env, status);
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
	ft_lstclear_data(&env);
	free_cmd_struct(c);
	ft_lstclear_minishell(l);
	//printf("%s\n", path);
	execve(path, args, env_tab);
	free_char_tab(args);
	free_char_tab(env_tab);
	free(path);
	exit(EXIT_FAILURE);
}

int	execute_cmds_exit(t_cmd_tab **cmd_struct, t_norm_exec *normy)
{
	child_process = 0;
	unlink("heredoc_tmp.txt");
	free_cmd_struct(cmd_struct);
	if (normy->exit != 257)
		return (normy->exit % 256);
	return (257);
}

void	e_c_i_c(t_norm_exec *normy, pid_t *pid, t_cmd_tab *current, t_data **env)
{
	int	saved_stdout;

	if (in_builtin(current->args[0]))
	{
		if (!current->next)
		{
			normy->output = 1;
			exec_builtin(current->args, normy, env, current);
		}
		else
		{
			pipe(normy->pipefd);
			saved_stdout = dup(STDOUT_FILENO);
			dup2(normy->pipefd[1], STDOUT_FILENO);
			exec_builtin(current->args, normy, env, current);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
			close(normy->pipefd[1]);
		}
	}
	else
	{
		pipe(normy->pipefd);
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
	normy->exit = 257;
	normy->output = 0;
}

int	execute_cmds(t_cmd_tab **c_s, t_cmd_tab *cu, t_data **env, t_parsing **l)
{
	t_norm_exec	normy;

	init_exec(&normy);
	normy.pids = ft_calloc(sizeof(pid_t), count_cmds(*c_s));
	while (cu)
	{
		if (cu->exec)
		{
			e_c_i_c(&normy, &normy.pids[normy.num_cmds], cu, env);
			if (normy.pids[normy.num_cmds] == 0 && !in_builtin(cu->cmd_name))
			{
				execute_child1(cu, normy.input_fd, normy.pipefd);
				execute_child2(cu, *env, l, c_s);
			}
			else if (normy.pids[normy.num_cmds] < 0)
				return (0);
			else
			{
				execute_cmds_parent(&normy.input_fd);
				normy.input_fd = (!in_builtin(cu->cmd_name) && close(normy.pipefd[1]));
				normy.input_fd = normy.pipefd[0];
			}
			normy.num_cmds++;
		}
		cu = cu->next;
	}
	exit_env(&normy, *env, c_s);
	return (execute_cmds_exit(c_s, &normy));
}

int	prompt_execution(t_parsing **lexing, t_data **env)
{
	t_cmd_tab	*first;

	first = NULL;
	lexing_to_cmd_tab(*lexing, &first);
	if (!find_place_path(&first, *env))
	{
		//printf("erreur dans le path\n");
	}
	return (execute_cmds(&first, first, env, lexing));
}
