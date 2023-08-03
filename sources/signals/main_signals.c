/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:01 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 08:49:36 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	int		i;
	char	spaces[51];

	(void)sig;
	if (g_child_process == 1)
	{
		printf("\n^C\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		g_child_process = -1;
		i = -1;
		while (++i < 50)
			spaces[i] = ' ';
		spaces[i] = '\0';
		printf("%s%s^C%s\n", rl_prompt, rl_line_buffer, spaces);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_child_process == 1)
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
