/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:09:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:10:57 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_fork(t_philosopher *philosopher, int fork, bool state)
{
	pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
	philosopher->data->forks[fork] = state;
	pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
	return (0);
}

int	set_end(t_data **data, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	(*data)->end = true;
	pthread_mutex_unlock(mutex);
	return (0);
}

int	set_fed(t_philosopher *philosopher, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	philosopher->fed = true;
	pthread_mutex_unlock(mutex);
	return (0);
}
