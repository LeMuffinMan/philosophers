/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:53:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:41:41 by oelleaum         ###   ########lyon.fr   */
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

bool	get_fork_state(t_philosopher *philosopher, int i)
{
	bool	exit_code;

	exit_code = false;
	pthread_mutex_lock(&philosopher->data->forks_mutex[i]);
	if (philosopher->data->forks[i] == true)
	{
		exit_code = true;
		philosopher->data->forks[i] = false;
	}
	pthread_mutex_unlock(&philosopher->data->forks_mutex[i]);
	return (exit_code);
}

long int	get_elapsed_time_since_last_meal(t_data **data,
		long int last_meal_time)
{
	long int	time_elapsed;

	pthread_mutex_lock(&(*data)->time_mutex);
	time_elapsed = get_time() - (*data)->start_time - last_meal_time;
	pthread_mutex_unlock(&(*data)->time_mutex);
	return (time_elapsed);
}
