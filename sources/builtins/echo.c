/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:34:13 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/23 17:52:13 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Fonction qui s'assure de la presence de '\n' a la fin des parametres
de echo s'il y en a un on ne fait rien, sinon on en rajoute un*/

int	ft_strcmp_minishell(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (ERROR);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**newline_terminated(char **echo, int size_echo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size_echo - 1)
		i++;
	while (echo[i][j])
		j++;
	if (echo[i][j - 1] != '\n')
		echo[i] = ft_strjoin(echo[i], "\n");
	return (echo);
}

/*Builtin de la commande echo*/

void	builtin_echo(char **echo, int fd)
{
	int	i;
	int	size_echo;

	i = 1;
	size_echo = ft_strlen_plus(echo);
	echo = newline_terminated(echo, size_echo);
	if (ft_strcmp_minishell(echo[1], "-n") == TRUE)
	{
		while (i < (size_echo - 1))
			i++;
		remove_newline(echo + i);
		i = 2;
	}
	while (echo[i])
	{
		ft_putstr_fd(echo[i], fd);
		if (i != size_echo)
			ft_putchar_fd(' ', fd);
		i++;
	}
}

// int	main()
// {
// 	char	*cmd_line;

// 	while (42)
// 	{
// 		ft_printf("minishell> ");
// 		cmd_line = get_next_line(0);
// 		builtin_echo(ft_split(cmd_line, ' '));
// 	}
// 	return (0);
// }