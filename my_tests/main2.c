/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:34:57 by amontign          #+#    #+#             */
/*   Updated: 2023/07/14 12:58:00 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];
	int pid1;
	int pid2;
	char *filename = "/bin/yes";
	char *argv[] = { "yes", NULL };
	char *envp[] = { NULL };
	char *filename2 = "/bin/head";
	char *argv2[] = { "head", "-1", NULL };

	if (pipe(fd) == -1)
	{
		//error
		return (1);
	}

	pid1 = fork();
	if (pid1 == -1)
	{
		//error
		return (1);
	}

	if (pid1 == 0)
	{
		//child 1
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(filename, argv, envp);
		//si on arrive ici, il y a une erreur
		return (1);
	}

	pid2 = fork();
	if (pid2 == -1)
	{
		//error
		return (1);
	}
	if (pid2 == 0)
	{
		//child 2
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(filename2, argv2, envp);
		//si on arrive ici, il y a une erreur
		return (1);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}