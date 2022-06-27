/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:02:19 by heboni            #+#    #+#             */
/*   Updated: 2022/06/27 14:03:01 by heboni           ###   ########.fr       */
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

# define PHILO_DEATH 256

# define INPUT_ERROR -1
# define STACK_OVERFLOW -2
# define PROCESS_ERROR -3
# define SEM_ERROR -4
# define PTHREAD_ERROR -5
# define SYSTIME_ERROR -6

typedef struct s_ctx	t_ctx;

struct s_ctx {
	int					philos_count;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					meals_count;

	int					*pids;
	unsigned long long	start_time;
	int					philo_n;
	int					meals_n;

	sem_t				*sem_forks;
	sem_t				*sem_stdout;
	sem_t				*sem_meal_time;
	sem_t				*sem_death_print;
	sem_t				*sem_taking_forks;

	unsigned long long	last_meal_time;
};

// main.c
int					ctx_init(t_ctx *ctx, char **argv);
void				semaphores_init(t_ctx *ctx);

// philos_simulation.c
void				philos_simulation(t_ctx *ctx, int philo_count);
void				philo_process(t_ctx *ctx, int i);
void				philo_life(t_ctx *ctx);
void				philos_simulation_end(t_ctx *ctx, int pid);
void				semaphores_close(t_ctx *ctx);

// check_end.c
void				*check_end(void *ph_data);
int					check_philo_death(t_ctx *ctx);

// philo_bonus_utils.c
void				get_current_ms_time(unsigned long long *time, t_ctx *ctx);
unsigned long long	get_ms_time_from_start(t_ctx *ctx);
void				print(char *s, t_ctx *ctx, int philo_n);
void				error_handler(char *str, int error_code, t_ctx *ctx);

int					ft_atoi(const char *str);
void				ft_usleep(int ms, t_ctx *ctx);

#endif