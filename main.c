/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:54:35 by heboni            #+#    #+#             */
/*   Updated: 2022/06/19 12:13:42 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_ctx	*ctx;
	int		philo_count;

	philo_count = ft_atoi(argv[1]);
	if ((argc != 5 && argc != 6) || philo_count == 0)
		return (INPUT_ERROR);
	ctx = (t_ctx *)malloc(sizeof(t_ctx));
	if (ctx == NULL)
		return (STACK_OVERFLOW);
	ctx_init(ctx, argv);
	philos_simulation(philo_count);//создание процессов-философов
	
	//в конце каждого процесса закрывать семафор sem_close
	return (0);
}

int	philos_simulation(int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count) //создавать процесссы только из родительского процесса
	{
		//if (parent_process)
		//		fork();
	}
	//обработка успешного создания дочерних процессов
}

int	ctx_init(t_ctx *ctx, char **argv)
{
	ctx->philos_count = ft_atoi(argv[1]);
	ctx->die_time = ft_atoi(argv[2]);
	ctx->eat_time = ft_atoi(argv[3]);
	ctx->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
	{
		ctx->meals_count = ft_atoi(argv[5]);
		if (ctx->meals_count <= 0)
			exit(error_print("Input error: \
					meals_count should be positive."));
	}
	else
		ctx->meals_count = -1;
	sem_unlink("/forks");
	ctx->sem_forks = sem_open("/forks", O_CREAT, 0777, ctx->philos_count);  
	return (0);
}