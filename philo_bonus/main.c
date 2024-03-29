/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:54:35 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 16:05:45 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_ctx	*ctx;
	int		philo_count;

	if (argc != 5 && argc != 6)
		exit (INPUT_ERROR);
	philo_count = ft_atoi(argv[1]);
	ctx = (t_ctx *)malloc(sizeof(t_ctx));
	if (ctx == NULL)
		return (STACK_OVERFLOW);
	ctx_init(ctx, argv);
	get_current_ms_time(&ctx->start_time, ctx);
	philos_simulation(ctx, philo_count);
	return (0);
}

int	ctx_init(t_ctx *ctx, char **argv)
{
	ctx->philos_count = ft_atoi(argv[1]);
	ctx->die_time = ft_atoi(argv[2]);
	ctx->eat_time = ft_atoi(argv[3]);
	ctx->sleep_time = ft_atoi(argv[4]);
	if (ctx->philos_count <= 0 || ctx->die_time < 0 || \
						ctx->eat_time < 0 || ctx->sleep_time < 0)
		error_handler("Input error: values should be positive.", \
						INPUT_ERROR, ctx);
	if (argv[5])
	{
		ctx->meals_count = ft_atoi(argv[5]);
		if (ctx->meals_count <= 0)
			error_handler("Input error: values should be positive.", \
							INPUT_ERROR, ctx);
	}
	else
		ctx->meals_count = -1;
	ctx->meals_n = 0;
	ctx->pids = (int *)malloc(sizeof(int) * ctx->philos_count);
	if (!ctx->pids)
		exit(STACK_OVERFLOW);
	semaphores_init(ctx);
	return (0);
}

void	semaphores_init(t_ctx *ctx)
{
	sem_unlink("/forks");
	ctx->sem_forks = sem_open("/forks", O_CREAT, 0777, ctx->philos_count);
	if (ctx->sem_forks == SEM_FAILED)
		exit(SEM_ERROR);
	sem_unlink("/stdout");
	ctx->sem_stdout = sem_open("/stdout", O_CREAT, 0777, 1);
	if (ctx->sem_stdout == SEM_FAILED)
		exit(SEM_ERROR);
	sem_unlink("/take_forks");
	ctx->sem_taking_forks = sem_open("/take_forks", O_CREAT, 0777, 1);
	if (ctx->sem_taking_forks == SEM_FAILED)
		exit(SEM_ERROR);
	sem_unlink("/death_print");
	ctx->sem_death_print = sem_open("/death_print", O_CREAT, 0777, 1);
	if (ctx->sem_death_print == SEM_FAILED)
		exit(SEM_ERROR);
}
