/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:05:58 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 15:17:24 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *ph_data)
{
	t_philo_ctx			*philo_ctx;

	philo_ctx = (t_philo_ctx *)ph_data;
	philo_life_init(philo_ctx);
	while (1)
	{
		pthread_mutex_lock(&philo_ctx->ctx->m_die);
		if (philo_ctx->ctx->must_die == 1)
		{
			pthread_mutex_unlock(&philo_ctx->ctx->m_die);
			return (NULL);
		}
		pthread_mutex_unlock(&philo_ctx->ctx->m_die);
		pthread_mutex_lock(&(philo_ctx->ctx->entry_p));
		pthread_mutex_lock(&philo_ctx->ctx->forks_m[philo_ctx->philo->left]);
		philo_print(philo_ctx, "has taken a fork", 0);
		if (philo_ctx->ctx->philo_count == 1)
		{
			one_philo_death(philo_ctx);
			return (NULL);
		}
		pthread_mutex_lock(&philo_ctx->ctx->forks_m[philo_ctx->philo->right]);
		pthread_mutex_unlock(&(philo_ctx->ctx->entry_p));
		philo_routine(philo_ctx);
	}
}

void	philo_life_init(t_philo_ctx *philo_ctx)
{
	if (philo_ctx->philo->philo_n == 1)
	{
		pthread_mutex_lock(&philo_ctx->ctx->m_start_time);
		get_current_ms_time(&philo_ctx->ctx->start_time);
		pthread_mutex_unlock(&philo_ctx->ctx->m_start_time);
	}
	if (philo_ctx->philo->philo_n % 2 == 0)
		usleep(500);
}

void	one_philo_death(t_philo_ctx *philo_ctx)
{
	pthread_mutex_lock(&philo_ctx->ctx->m_die);
	philo_ctx->ctx->must_die = 1;
	pthread_mutex_unlock(&philo_ctx->ctx->m_die);
	pthread_mutex_unlock(&philo_ctx->ctx->forks_m[philo_ctx->philo->left]);
	pthread_mutex_unlock(&(philo_ctx->ctx->entry_p));
}

void	philo_routine(t_philo_ctx *philo_ctx)
{
	unsigned long long	time;

	get_ms_time_from_start(philo_ctx->ctx, &time);
	philo_print(philo_ctx, "has taken a fork", &time);
	pthread_mutex_lock(&philo_ctx->ctx->m_meal_time);
	philo_ctx->philo->last_meal_time = time;
	pthread_mutex_unlock(&philo_ctx->ctx->m_meal_time);
	philo_print(philo_ctx, "is eating", &time);
	if (philo_ctx->philo->meals_n == philo_ctx->ctx->meals_count)
	{
		pthread_mutex_lock(&philo_ctx->ctx->m_phs_eaten);
		philo_ctx->ctx->phs_eaten_count++;
		pthread_mutex_unlock(&philo_ctx->ctx->m_phs_eaten);
	}
	ft_usleep(philo_ctx->ctx->eat_time);
	pthread_mutex_unlock(&philo_ctx->ctx->forks_m[philo_ctx->philo->left]);
	pthread_mutex_unlock(&philo_ctx->ctx->forks_m[philo_ctx->philo->right]);
	philo_ctx->philo->meals_n++;
	philo_print(philo_ctx, "is sleeping", 0);
	ft_usleep(philo_ctx->ctx->sleep_time);
	philo_print(philo_ctx, "is thinking", 0);
}
