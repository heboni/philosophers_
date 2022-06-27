/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:06:46 by heboni            #+#    #+#             */
/*   Updated: 2022/06/25 15:50:10 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(int ms)
{
	unsigned long long		start;
	unsigned long long		current;

	if (get_current_ms_time(&start) || get_current_ms_time(&current))
		return (1);
	while ((current - start) < (unsigned long long)ms)
	{
		usleep(100);
		if (get_current_ms_time(&current))
			return (1);
	}
	return (0);
}
