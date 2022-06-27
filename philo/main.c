/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:04:05 by heboni            #+#    #+#             */
/*   Updated: 2022/06/26 23:10:10 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ctx		*ctx;
	t_philo		*philos;
	t_philo_ctx	*philos_ctx;
	int			philo_count;

	philo_count = ft_atoi(argv[1]);
	if ((argc != 5 && argc != 6) || philo_count == 0)
		return (INPUT_ERROR);
	ctx = (t_ctx *)malloc(sizeof(t_ctx));
	if (ctx == NULL)
		return (STACK_OVERFLOW);
	if (ctx_init(ctx, argv))
		return (-1);
	philos = (t_philo *)malloc(sizeof(t_philo) * philo_count);
	if (philos == NULL)
		return (STACK_OVERFLOW);
	philos_init(philos, philo_count);
	philos_ctx = (t_philo_ctx *)malloc(sizeof(t_philo_ctx) * philo_count);
	if (philos_ctx == NULL)
		return (STACK_OVERFLOW);
	philos_ctx_init(ctx, philos, philos_ctx);
	philos_simulation(philos_ctx, philo_count);
	memory_free(philos_ctx, philos);
	return (0);
}

int	philos_simulation(t_philo_ctx *philos_ctx, int philo_count)
{
	pthread_t	*thid;
	pthread_t	end_thid;
	int			i;

	i = -1;
	thid = (pthread_t *)malloc(sizeof(pthread_t) * philo_count);
	if (thid == NULL)
		return (error_print("An malloc error occured.", 0));
	while (++i < philo_count)
	{
		if (pthread_create(&thid[i], NULL, philo_life, &philos_ctx[i]))
			return (error_print("An pthread_create error occured.", 0));
	}
	if (pthread_create(&end_thid, NULL, check_end, philos_ctx))
		return (error_print("An pthread_create error occured.", 0));
	threads_join(thid, &end_thid, &philos_ctx->ctx->philo_count);
	free(thid);
	if (mutex_destroy(philos_ctx->ctx))
		return (error_print("An pthread_mutex_destroy error occured.", 0));
	return (0);
}

int	threads_join(pthread_t *thid, pthread_t *end_thid, int *philo_count)
{
	int	i;

	i = -1;
	if (pthread_join(*end_thid, 0))
		return (error_print("An pthread_join error occured.", 0));
	while (++i < *philo_count)
	{
		if (pthread_join(thid[i], 0))
			return (error_print("An pthread_join error occured.", 0));
	}
	return (0);
}
