/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:12:16 by heboni            #+#    #+#             */
/*   Updated: 2022/06/26 23:01:13 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_philo_ctx *philo_ctx, char *s, unsigned long long *t)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo_ctx->ctx->m_die);
	if (philo_ctx->ctx->must_die == 1)
	{
		pthread_mutex_unlock(&philo_ctx->ctx->m_die);
		return (0);
	}
	pthread_mutex_unlock(&philo_ctx->ctx->m_die);
	if (t == 0)
	{
		if (get_ms_time_from_start(philo_ctx->ctx, &time))
			return (1);
		print(philo_ctx, s, &time);
	}
	else
		print(philo_ctx, s, t);
	return (0);
}

void	print(t_philo_ctx *philo_ctx, char *s, unsigned long long *time)
{
	pthread_mutex_lock(&philo_ctx->ctx->m_print);
	printf("%llu %d %s\n", *time, philo_ctx->philo->philo_n, s);
	pthread_mutex_unlock(&philo_ctx->ctx->m_print);
}

int	get_current_ms_time(unsigned long long *time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		return (error_print("An gettimeofday error occured.", NULL));
	*time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

int	get_ms_time_from_start(t_ctx *ctx, unsigned long long *time_from_start)
{
	unsigned long long	current;

	if (get_current_ms_time(&current))
		return (1);
	*time_from_start = current - ctx->start_time;
	return (0);
}

int	error_print(char *str, t_ctx *ctx)
{
	printf("%s\n", str);
	if (ctx)
		free(ctx);
	return (1);
}

// int	error_print(char *str)
// {
// 	printf("%s\n", str);
// 	return (1);
// }
