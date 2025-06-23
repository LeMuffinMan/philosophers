/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 17:08:25 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philosopher *philosopher)
{
	if (is_simulation_over(philosopher))
		return (1);
	if (print_log(&philosopher->data, philosopher, "is thinking"))
		return (1);
	accurate_sleep(&philosopher->data, philosopher->time_to_eat * 2
		- philosopher->time_to_sleep);
	if (is_simulation_over(philosopher))
		return (1);
	return (0);
}

int	eating(t_philosopher *philosopher)
{
	if (is_simulation_over(philosopher))
		return (1);
	if (print_log(&philosopher->data, philosopher, "is eating"))
		return (1);
	philosopher->nb_meals_eaten++;
	if (philosopher->nb_meals_eaten == philosopher->meals_limit)
		set_fed(philosopher, &philosopher->fed_mutex);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal = get_time(&philosopher->data)
		- philosopher->start_time;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	if (is_simulation_over(philosopher))
		return (1);
	accurate_sleep(&philosopher->data, philosopher->time_to_eat);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal = get_time(&philosopher->data)
		- philosopher->start_time;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	if (is_simulation_over(philosopher))
		return (1);
	return (0);
}

int	sleeping(t_philosopher *philosopher)
{
	if (print_log(&philosopher->data, philosopher, "is sleeping"))
		return (1);
	accurate_sleep(&philosopher->data, philosopher->time_to_sleep);
	return (0);
}

bool	sync_threads_start(t_philosopher *philosopher)
{
	long int	start_time;

	start_time = is_time_started(philosopher);
	while (start_time < 0)
	{
		if (is_simulation_over(philosopher))
			return (1);
		start_time = is_time_started(philosopher);
	}
	philosopher->start_time = start_time;
	if (philosopher->id % 2 == 0)
		accurate_sleep(&philosopher->data, 10);
	return (0);
}

void	*philosophers_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (sync_threads_start(philosopher))
		return (NULL);
	while (!is_simulation_over(philosopher))
	{
		if (!take_two_forks(philosopher))
			return (NULL);
		if (is_simulation_over(philosopher))
			return (NULL);
		if (eating(philosopher))
		{
			release_forks(philosopher);
			return (NULL);
		}
		if (release_forks(philosopher))
			return (NULL);
		if (is_simulation_over(philosopher))
			return (NULL);
		if (sleeping(philosopher) || thinking(philosopher))
			return (NULL);
	}
	return (NULL);
}
