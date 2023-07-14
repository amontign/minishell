/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:47:26 by amontign          #+#    #+#             */
/*   Updated: 2023/07/14 11:32:41 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	arr[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	int	arrSize = sizeof(arr) / sizeof(int);
	int fd[2];
	int	id;
	int	start;
	int	end;
	int	sum;
	int	i;
	int	sumChildRead;
	int	totalSum;
	
	if (pipe(fd) == -1)
	{
		//error
		return (1);
	}
	id = fork();
	if (id == -1)
	{
		//error
		return (1);
	}

	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else {
		start = arrSize / 2;
		end = arrSize;
	}

	sum = 0;
	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	
	printf("Somme partielle : %d\n", sum);

	if (id == 0)
	{
		if (write(fd[1], &sum, sizeof(sum)) == -1)
		{
			//error
			return (1);
		}
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[1]);
		if (read(fd[0], &sumChildRead, sizeof(sumChildRead)) == -1)
		{
			//error
			return (1);
		}
		close(fd[0]);

		totalSum = sum + sumChildRead;
		printf("total sum is %d\n", totalSum);
	}

	return (0);
}