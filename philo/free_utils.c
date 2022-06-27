/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heboni <heboni@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:08:52 by heboni            #+#    #+#             */
/*   Updated: 2022/06/06 22:09:37 by heboni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	memory_free(t_philo_ctx *philos_ctx, t_philo *philos)
{
	free(philos_ctx->ctx->forks_m);
	free(philos_ctx->ctx);
	free(philos_ctx);
	free(philos);
}

int	mutex_destroy(t_ctx *ctx)
{
	int	i;

	i = -1;
	if (pthread_mutex_destroy(&ctx->m_meal_time))
		return (1);
	if (pthread_mutex_destroy(&ctx->m_start_time))
		return (1);
	if (pthread_mutex_destroy(&ctx->m_die))
		return (1);
	if (pthread_mutex_destroy(&ctx->m_phs_eaten))
		return (1);
	if (pthread_mutex_destroy(&ctx->m_print))
		return (1);
	if (pthread_mutex_destroy(&ctx->entry_p))
		return (1);
	while (++i < ctx->philo_count)
	{
		if (pthread_mutex_destroy(&ctx->forks_m[i]))
			return (1);
	}
	return (0);
}
