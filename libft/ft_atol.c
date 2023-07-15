/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:34:45 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:18:38 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_atol(char *nptr)
{
	long	sign;
	long	rslt;

	sign = 1;
	rslt = 0;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr > 47 && *nptr < 58)
	{
		rslt = rslt * 10 + (*nptr - '0');
		nptr++;
	}
	rslt *= sign;
	return (rslt);
}
