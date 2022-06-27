/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:15:19 by heboni            #+#    #+#             */
/*   Updated: 2022/06/26 23:01:55 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ctx_init(t_ctx *ctx, char **argv)
{
	ctx->philo_count = ft_atoi(argv[1]);
	ctx->die_time = ft_atoi(argv[2]);
	ctx->eat_time = ft_atoi(argv[3]);
	ctx->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
	{
		ctx->meals_count = ft_atoi(argv[5]);
		if (ctx->meals_count <= 0)
			return (error_print("Input error: \
					meals_count should be positive.", ctx));
	}
	else
		ctx->meals_count = -1;
	if (ctx->die_time < 0 || ctx->eat_time < 0 || ctx->sleep_time < 0)
		return (error_print("Input error: \
					values should be positive.", ctx));
	ctx->phs_eaten_count = 0;
	ctx->forks_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
												* ctx->philo_count);
	if (ctx->forks_m == NULL)
		return (-2);
	mutex_init(ctx);
	return (0);
}

void	mutex_init(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philo_count)
		pthread_mutex_init(&ctx->forks_m[i], NULL);
	pthread_mutex_init(&ctx->m_meal_time, NULL);
	pthread_mutex_init(&ctx->m_start_time, NULL);
	pthread_mutex_init(&ctx->m_die, NULL);
	pthread_mutex_init(&ctx->m_phs_eaten, NULL);
	pthread_mutex_init(&ctx->m_print, NULL);
	pthread_mutex_init(&ctx->entry_p, NULL);
}

void	philos_init(t_philo *philos, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		philos[i].philo_n = i + 1;
		philos[i].meals_n = 0;
		philos[i].right = i;
		if (philo_count == 1)
		{
			philos[i].left = 0;
			return ;
		}
		if (philos[i].philo_n != philo_count)
			philos[i].left = i + 1;
		else
			philos[i].left = 0;
	}
}

void	philos_ctx_init(t_ctx *ctx, t_philo *philos, t_philo_ctx *philos_ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philo_count)
	{
		philos_ctx[i].ctx = ctx;
		philos_ctx[i].philo = &philos[i];
	}
}
