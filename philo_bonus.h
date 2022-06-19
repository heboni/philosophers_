/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:02:19 by heboni            #+#    #+#             */
/*   Updated: 2022/06/19 09:25:05 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h> //fork
# include <stdlib.h> //malloc free
# include <stdio.h> //printf
# include <signal.h> //kill
# include <pthread.h> 
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h> //waitpid

# define INPUT_ERROR -1
# define STACK_OVERFLOW -2

typedef struct s_ctx	t_ctx;

struct s_ctx {
	int		philos_count;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		meals_count;

	sem_t	*sem_forks;
};

int	ctx_init(t_ctx *ctx, char **argv);

#endif