/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:06:46 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 09:32:19 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(int ms, t_ctx *ctx)
{
	unsigned long long		start;
	unsigned long long		current;

	get_current_ms_time(&start, ctx);
	get_current_ms_time(&current, ctx);
	while ((current - start) < (unsigned long long)ms)
	{
		usleep(10);
		get_current_ms_time(&current, ctx);
	}
}
