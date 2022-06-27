/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:02:37 by heboni            #+#    #+#             */
/*   Updated: 2022/06/26 23:00:20 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define INPUT_ERROR -1
# define STACK_OVERFLOW -2

typedef struct s_context	t_ctx;
typedef struct s_philo		t_philo;
typedef struct s_philo_ctx	t_philo_ctx;

struct s_context
{
	int					philo_count;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					meals_count;

	int					phs_eaten_count;
	int					must_die;
	unsigned long long	start_time;

	pthread_mutex_t		entry_p;
	pthread_mutex_t		m_phs_eaten;
	pthread_mutex_t		m_start_time;
	pthread_mutex_t		m_meal_time;
	pthread_mutex_t		m_die;
	pthread_mutex_t		m_print;
	pthread_mutex_t		*forks_m;
};

struct s_philo
{
	int					philo_n;
	int					meals_n;

	int					left;
	int					right;

	unsigned long long	last_meal_time;
};

struct s_philo_ctx {
	t_ctx	*ctx;
	t_philo	*philo;
};

//init.c
int		ctx_init(t_ctx *ctx, char **argv);
void	mutex_init(t_ctx *ctx);
void	philos_init(t_philo *philos, int philo_count);
void	philos_ctx_init(t_ctx *ctx, t_philo *philos, t_philo_ctx *philos_ctx);

//main.c
int		philos_simulation(t_philo_ctx *philos_ctx, int philo_count);
int		threads_join(pthread_t *thid, pthread_t *end_thid, int *philo_count);

//philo.c
void	*philo_life(void *philo);
void	philo_life_init(t_philo_ctx *philo_ctx);
void	one_philo_death(t_philo_ctx *philo_ctx);
void	philo_routine(t_philo_ctx *philo_ctx);

//check_end.c
void	*check_end(void *ph_data);
int		check_philos_eaten(t_philo_ctx *philos_ctx);
int		check_philo_death(t_philo_ctx *philos_ctx);
void	set_must_die(t_philo_ctx *philo_ctx, unsigned long long *now_ms);

//philo_utils.c
int		philo_print(t_philo_ctx *philo_ctx, char *s, unsigned long long *t);
void	print(t_philo_ctx *philo_ctx, char *s, unsigned long long *time);
int		get_current_ms_time(unsigned long long *time);
int		get_ms_time_from_start(t_ctx *ctx, unsigned long long *time_from_start);
int		error_print(char *str, t_ctx *ctx); // int		error_print(char *str);

//free_utils
int		mutex_destroy(t_ctx *ctx);
void	memory_free(t_philo_ctx *philos_ctx, t_philo *philos);

//ft_usleep
int		ft_usleep(int ms);

//ft_atoi
int		ft_atoi(const char *str);

#endif