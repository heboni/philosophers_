/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:26:50 by heboni            #+#    #+#             */
/*   Updated: 2022/06/06 22:39:27 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_end(void *ph_data)
{
	int			i;
	t_philo_ctx	*philos_ctx;

	philos_ctx = (t_philo_ctx *)ph_data;
	while (1)
	{
		i = -1;
		while (++i < philos_ctx->ctx->philo_count)
		{
			if (check_philo_death(&philos_ctx[i]))
				return (0);
			if (check_philos_eaten(philos_ctx))
				return (0);
		}
	}
}

int	check_philo_death(t_philo_ctx *philo_ctx)
{
	unsigned long long	now_ms;
	unsigned long long	die_time;

	if (get_current_ms_time(&now_ms))
		return (1);
	die_time = (unsigned long long) philo_ctx->ctx->die_time;
	pthread_mutex_lock(&philo_ctx->ctx->m_meal_time);
	pthread_mutex_lock(&philo_ctx->ctx->m_start_time);
	if (philo_ctx->ctx->start_time != 0)
	{
		if ((philo_ctx->philo->last_meal_time != 0 && now_ms - \
			philo_ctx->ctx->start_time - philo_ctx->philo->last_meal_time \
			> die_time) || (philo_ctx->philo->last_meal_time == 0 && now_ms - \
			philo_ctx->ctx->start_time > die_time))
		{
			pthread_mutex_unlock(&philo_ctx->ctx->m_meal_time);
			pthread_mutex_unlock(&philo_ctx->ctx->m_start_time);
			set_must_die(philo_ctx, &now_ms);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo_ctx->ctx->m_meal_time);
	pthread_mutex_unlock(&philo_ctx->ctx->m_start_time);
	return (0);
}

void	set_must_die(t_philo_ctx *philo_ctx, unsigned long long *now_ms)
{
	pthread_mutex_lock(&philo_ctx->ctx->m_die);
	philo_ctx->ctx->must_die = 1;
	pthread_mutex_unlock(&philo_ctx->ctx->m_die);
	printf("%llu %d died\n", *now_ms - philo_ctx->ctx->start_time, \
										philo_ctx->philo->philo_n);
}

int	check_philos_eaten(t_philo_ctx *philos_ctx)
{
	pthread_mutex_lock(&philos_ctx->ctx->m_phs_eaten);
	if (philos_ctx->ctx->phs_eaten_count == philos_ctx->ctx->philo_count)
	{
		pthread_mutex_unlock(&philos_ctx->ctx->m_phs_eaten);
		pthread_mutex_lock(&philos_ctx->ctx->m_die);
		philos_ctx->ctx->must_die = 1;
		pthread_mutex_unlock(&philos_ctx->ctx->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philos_ctx->ctx->m_phs_eaten);
	return (0);
}
