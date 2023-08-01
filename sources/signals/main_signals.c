/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:01 by amontign          #+#    #+#             */
/*   Updated: 2023/08/01 13:14:21 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	int		i;
	char	*spaces;

	(void)sig;
	if (child_process == 1)
	{
		printf("\n^C\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{

		child_process = -1;
		spaces = malloc(sizeof(char) * (50 + 1));
		i = -1;
		while (++i < 50)
			spaces[i] = ' ';
		spaces[i] = '\0';
		printf("%s%s^C%s\n", rl_prompt, rl_line_buffer, spaces);
		free(spaces);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (child_process == 1)
	{
		printf("^\\Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	main_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
