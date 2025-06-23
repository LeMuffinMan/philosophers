/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:53:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 17:21:56 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_fed_state(t_philosopher *philosopher)
{
	bool	state;

	pthread_mutex_lock(&philosopher->fed_mutex);
	state = philosopher->fed;
	pthread_mutex_unlock(&philosopher->fed_mutex);
	return (state);
}

long int	get_last_meal_time(t_philosopher *philosopher)
{
	long int	last_meal_time;

	pthread_mutex_lock(&philosopher->last_meal_mutex);
	last_meal_time = philosopher->last_meal;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (last_meal_time);
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
