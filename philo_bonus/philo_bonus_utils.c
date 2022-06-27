/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:26:35 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 09:32:52 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_current_ms_time(unsigned long long *time, t_ctx *ctx)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		error_handler("An gettimeofday error occured.", SYSTIME_ERROR, ctx);
	*time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

unsigned long long	get_ms_time_from_start(t_ctx *ctx)
{
	unsigned long long	time_from_start;
	unsigned long long	current;

	get_current_ms_time(&current, ctx);
	time_from_start = current - ctx->start_time;
	return (time_from_start);
}

void	print(char *s, t_ctx *ctx, int philo_n)
{
	sem_wait(ctx->sem_stdout);
	printf("%llu %d %s", get_ms_time_from_start(ctx), philo_n, s);
	sem_post(ctx->sem_stdout);
}

void	error_handler(char *str, int error_code, t_ctx *ctx)
{
	sem_wait(ctx->sem_stdout);
	printf("%s\n", str);
	sem_post(ctx->sem_stdout);
	if (error_code)
		exit(error_code);
}
