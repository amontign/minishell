/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:01 by amontign          #+#    #+#             */
/*   Updated: 2023/07/23 18:09:03 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (child_process == 1)
	{
		printf("\n^C\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("%s%s^C\n", rl_prompt, rl_line_buffer);
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
		printf("Quit (core dumped)\n");
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
