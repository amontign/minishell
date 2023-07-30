/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:00:49 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/30 16:53:16 by cbernaze         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (cmd_line[i] && (cmd_line[i] == ' '
			|| (cmd_line[i] > 6 && cmd_line[i] < 14)))
		i++;
	if (cmd_line[i] == '\0')
		return ;
	if (syntax(cmd_line) == ERROR_SYNTAX)
	 	return ;
	*lexing = tokenisation(cmd_line);
	final_parsing(lexing);
	if (*lexing)
	{
		expand(lexing, env);
		if (*lexing)
			print_cmd(*lexing);
	}
}

/*This function makes a prompt on the terminal, reads the command line
then launches the parsing and the execution.*/

int	minishell_prompt(t_data **env)
{
	t_parsing	*lexing;
	char		*cmd_line;
	// char		*name_eval;
	// char		*prompt_char;
	int			ret;

	lexing = NULL;
	ret = 0;
	// name_eval = readline("Hello evaluator, tell me your name : ");
	// remove_newline(&name_eval);
	// prompt_char = ft_strjoin(name_eval, "@minishell> ");
	// free(name_eval);
	main_signal();
	while (42)
	{
		cmd_line = readline("minishell> ");
		if (!cmd_line)
			break ;
		remove_newline(&cmd_line);
		if (cmd_line[0] != '\0')
			add_history(cmd_line);
		parsing(&lexing, *env, cmd_line);
		free(cmd_line);
		ret = prompt_execution(&lexing, env);
		if (ret != 257)
			break ;
		ft_lstclear_minishell(&lexing);
	}
	printf("exit\n");
	// free(prompt_char);
	return (ret);
}

/*The environment is transformed into a chained list,
then either the prompt or non_interactive shell is launched.*/

int	main(int argc, char **argv, char **envp)
{
	t_data	*env;
	void	*verif;
	struct	termios oldt;
	struct	termios newt;
	int		ret;

	(void)argc;
	(void)argv;
	verif = malloc(3000);
	if (!verif)
		return (ft_printf("not enough memory available\n"), 42);
	free (verif);
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	env = NULL;
	ft_getenv(&env, envp);
	ret = minishell_prompt(&env);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	ft_lstclear_data(&env);
	return (ret);
}
