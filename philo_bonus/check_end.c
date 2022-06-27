/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:28:58 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 09:31:45 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_end(void *ph_data)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ph_data;
	while (1)
	{
		if (check_philo_death(ctx))
		{
			sem_wait(ctx->sem_death_print);
			sem_wait(ctx->sem_stdout);
			printf("%llu %d %s", get_ms_time_from_start(ctx), \
					ctx->philo_n, "died\n");
			exit (1);
		}
		if (ctx->meals_n == ctx->meals_count)
		{
			sem_post(ctx->sem_stdout);
			exit(0);
		}
	}
}

int	check_philo_death(t_ctx *ctx)
{
	unsigned long long	now_ms;
	unsigned long long	die_time;

	die_time = (unsigned long long) ctx->die_time;
	get_current_ms_time(&now_ms, ctx);
	sem_wait(ctx->sem_meal_time);
	if ((ctx->last_meal_time != 0 && \
			now_ms - ctx->start_time - ctx->last_meal_time > die_time) \
			|| (ctx->last_meal_time == 0 && \
			now_ms - ctx->start_time > die_time))
	{
		sem_post(ctx->sem_meal_time);
		return (1);
	}
	sem_post(ctx->sem_meal_time);
	return (0);
}
