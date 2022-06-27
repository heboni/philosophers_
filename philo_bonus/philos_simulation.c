/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 13:52:34 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 14:02:45 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philos_simulation(t_ctx *ctx, int philo_count)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < philo_count)
	{
		pid = fork();
		if (pid < 0)
			error_handler("An fork() error occured.", PROCESS_ERROR, ctx);
		else if (pid > 0)
			ctx->pids[i] = pid;
		else if (pid == 0)
		{
			philo_process(ctx, i + 1);
			break ;
		}
	}
	philos_simulation_end(ctx, pid);
}

void	philos_simulation_end(t_ctx *ctx, int pid)
{
	int	*must_die;
	int	i;

	i = -1;
	must_die = (int *)malloc(sizeof(int));
	if (pid > 0)
	{
		while ((waitpid(-1, must_die, 0) >= 0))
		{
			if (*must_die == PHILO_DEATH)
			{
				while (++i < ctx->philos_count)
					kill(ctx->pids[i], SIGKILL);
			}
		}
		free(must_die);
		free(ctx->pids);
		free(ctx);
		semaphores_close(ctx);
	}
}

void	semaphores_close(t_ctx *ctx)
{
	if (sem_close(ctx->sem_forks))
		exit(SEM_ERROR);
	if (sem_close(ctx->sem_stdout))
		exit(SEM_ERROR);
	if (sem_close(ctx->sem_taking_forks))
		exit(SEM_ERROR);
	if (sem_close(ctx->sem_death_print))
		exit(SEM_ERROR);
}

void	philo_process(t_ctx *ctx, int philo_n)
{
	pthread_t	end_thid;

	ctx->philo_n = philo_n;
	if (pthread_create(&end_thid, NULL, check_end, ctx))
		error_handler("An pthread_create error occured.", PTHREAD_ERROR, ctx);
	if (philo_n % 2 == 0)
		usleep(400);
	while (1)
		philo_life(ctx);
	if (pthread_join(end_thid, 0))
		error_handler("An pthread_join error occured.\n", PTHREAD_ERROR, ctx);
}

void	philo_life(t_ctx *ctx)
{
	sem_wait(ctx->sem_taking_forks);
	sem_wait(ctx->sem_forks);
	print("has taken a fork\n", ctx, ctx->philo_n);
	sem_wait(ctx->sem_forks);
	sem_post(ctx->sem_taking_forks);
	print("has taken a fork\n", ctx, ctx->philo_n);
	sem_wait(ctx->sem_meal_time);
	ctx->last_meal_time = get_ms_time_from_start(ctx);
	sem_post(ctx->sem_meal_time);
	print("is eating\n", ctx, ctx->philo_n);
	ft_usleep(ctx->eat_time, ctx);
	ctx->meals_n++;
	sem_post(ctx->sem_forks);
	sem_post(ctx->sem_forks);
	print("is sleeping\n", ctx, ctx->philo_n);
	ft_usleep(ctx->sleep_time, ctx);
	print("is thinking\n", ctx, ctx->philo_n);
}
