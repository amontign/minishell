/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:01 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 10:27:49 by amontign         ###   ########.fr       */
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
	char	*old_buffer;

	(void)sig;
	if (g_child_process == 1)
	{
		printf("^\\Quit (core dumped)\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		old_buffer = ft_strdup(rl_line_buffer);
		rl_on_new_line();
		rl_replace_line(old_buffer, 0);
		rl_redisplay();
		free(old_buffer);
	}
}

void	main_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
