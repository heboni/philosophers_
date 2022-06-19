/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:44:20 by heboni            #+#    #+#             */
/*   Updated: 2022/05/15 18:29:11 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	n;
	int	neg;
	int	i;

	n = 0;
	i = 0;
	neg = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' \
			|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (++i > 18)
		{
			if (neg == 1)
				return (-1);
			return (0);
		}
		n = n * 10 + (*str++ - '0');
	}
	return (n * neg);
}
