/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:09:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:41:57 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork(t_philosopher *philosopher, int fork, bool state)
{
	pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
	philosopher->data->forks[fork] = state;
	pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
}

void	set_end(t_data **data, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	(*data)->end = true;
	pthread_mutex_unlock(mutex);
}

void	set_fed(t_philosopher *philosopher, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	philosopher->fed = true;
	pthread_mutex_unlock(mutex);
}

bool	set_last_meal(t_philosopher *philosopher, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	philosopher->last_meal = get_time(&philosopher->data)
		- philosopher->start_time;
	if (philosopher->last_meal == GETTIMEOFDAY_ERROR)
		return (false);
	pthread_mutex_unlock(mutex);
	return (true);
}
