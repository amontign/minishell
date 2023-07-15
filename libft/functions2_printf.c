/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:05:01 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/15 09:03:57 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr_base_fd(unsigned long long int nbr, char *base, int fd)
{
	unsigned long long int	i;
	int						len;

	i = ft_strlen(base);
	len = 0;
	if (nbr < i)
	{
		write(fd, &(base[nbr]), 1);
		len += len +1;
	}
	else
	{
		len += ft_putnbr_base_fd(nbr / i, base, fd);
		len += ft_putnbr_base_fd(nbr % i, base, fd);
	}
	return (len);
}

int	ft_putvoid_fd(unsigned long long int nbr, char *base, int fd)
{
	int	len;

	len = 0;
	if (nbr == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	len += write(fd, "0x", 2);
	len += ft_putnbr_base_fd(nbr, base, fd);
	return (len);
}
