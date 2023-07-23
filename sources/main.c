/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:00:49 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/23 13:26:52 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int child_process;

/*This function removes the newline at the end of a command line.*/

void	remove_newline(char **name_eval)
{
	int	i;

	i = 0;
	while ((*name_eval)[i] != '\n' && (*name_eval)[i] != '\0')
		i++;
	(*name_eval)[i] = '\0';
	return ;
}

/*This function launches the parsing, the tokenisation, the expand and
returns the formated command line ready for the execution.*/

void	parsing(t_parsing **lexing, t_data *env, char *cmd_line)
{
	// if (parsing() == ERROR)
	// 	return ;
	*lexing = tokenisation(cmd_line);
	if (*lexing)
	{
		expand(lexing, env);
		//if (*lexing)
		//	print_cmd(*lexing);
	}
}

/*This function makes a prompt on the terminal, reads the command line
then launches the parsing and the execution.*/

void	minishell_prompt(t_data *env)
{
	t_parsing	*lexing;
	char		*cmd_line;
	char		*name_eval;
	char		*prompt_char;

	lexing = NULL;
	name_eval = readline("Hello evaluator, tell me your name : ");
	remove_newline(&name_eval);
	prompt_char = ft_strjoin(name_eval, "@minishell> ");
	free(name_eval);
	main_signal();
	while (42)
	{
		cmd_line = readline(prompt_char);
		if (!cmd_line)
			break ;
		remove_newline(&cmd_line);
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		parsing(&lexing, env, cmd_line);
		free(cmd_line);
		// execution
		prompt_execution(&lexing, env);
		// end of execution
		ft_lstclear_minishell(&lexing);
	}
	printf("exit\n");
	free(prompt_char);
}

/*This function is launched if we are not in the
interactive mode.*/

char	*ft_strdup_ms(const char *s)
{
	char	*dup;
	int		size_s;
	int		i;

	i = 0;
	size_s = ft_strlen(s);
	dup = (char *)malloc(sizeof(*s) * (size_s + 1));
	if (!dup)
		return (NULL);
	while (i < size_s && s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	non_interactive_sh(char **argv, char **envp)
{
	char	**cmd;

	cmd = NULL;
	if (is_not_command(argv[2], argv) == TRUE)
		(ft_printf("minishell: -c: option requires an argument"), exit(1));
	// if (redir_followed_by_cmd() == TRUE)
	// 	return (0);
	else
	{
		cmd = malloc(2 * sizeof(char*));
		cmd[0] = ft_strdup_ms(argv[2]);
		cmd[1] = NULL;
		exec_single_cmd(cmd, argv, envp);
	}
	(free(cmd[0]), free(cmd), exit(0));
}

/*The environment is transformed into a chained list,
then either the prompt or non_interactive shell is launched.*/

int	main(int argc, char **argv, char **envp)
{
	t_data	*env;
	void	*verif;
	struct termios oldt;
	struct termios newt;

	(void)argc;
	verif = malloc(3000);
	if (!verif)
		return (ft_printf("not enough memory available\n"), 42);
	free (verif);
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	env = NULL;
	if (ft_strcmp_minishell(argv[1], "c") == TRUE)
		non_interactive_sh(argv, envp);
	else
	{
		ft_getenv(&env, envp);
		minishell_prompt(env);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return (ft_lstclear_data(&env), 0);
}
