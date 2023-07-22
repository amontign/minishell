/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:01 by amontign          #+#    #+#             */
/*   Updated: 2023/07/22 16:18:34 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	if (child_process == 1)
	{
		exit(1);
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigquit(int sig)
{
	(void)sig;
	if (child_process != 1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		exit(1);
	}
}

void	main_signal(void)
{

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}