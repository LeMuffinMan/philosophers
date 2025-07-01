/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:49:21 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	thinking(t_philosopher *philosopher)
{
	long int	exit_code;

	if (is_simulation_over(philosopher))
		return (false);
	if (!print_log(&philosopher->data, philosopher, "is thinking", false))
		return (false);
	if (philosopher->nb_philo % 2 != 0)
	{
		exit_code = accurate_sleep(&philosopher->data, philosopher->time_to_eat
				* 2 - philosopher->time_to_sleep);
		if (exit_code == GETTIMEOFDAY_ERROR || exit_code == SIMULATION_END)
			return (false);
	}
	if (is_simulation_over(philosopher))
		return (false);
	return (true);
}

static bool	eating(t_philosopher *philosopher)
{
	long int	exit_code;

	if (is_simulation_over(philosopher))
		return (false);
	if (!print_log(&philosopher->data, philosopher, "is eating", false))
		return (false);
	if (!set_last_meal(philosopher, &philosopher->last_meal_mutex))
		return (false);
	if (is_simulation_over(philosopher))
		return (false);
	exit_code = accurate_sleep(&philosopher->data, philosopher->time_to_eat);
	if (exit_code == GETTIMEOFDAY_ERROR || exit_code == SIMULATION_END)
		return (false);
	philosopher->nb_meals_eaten++;
	if (philosopher->nb_meals_eaten == philosopher->meals_limit)
		set_fed(philosopher, &philosopher->fed_mutex);
	if (is_simulation_over(philosopher))
		return (false);
	return (true);
}

static bool	sleeping(t_philosopher *philosopher)
{
	long int	exit_code;

	if (!print_log(&philosopher->data, philosopher, "is sleeping", false))
		return (false);
	exit_code = accurate_sleep(&philosopher->data, philosopher->time_to_sleep);
	if (exit_code == GETTIMEOFDAY_ERROR || exit_code == SIMULATION_END)
		return (false);
	if (is_simulation_over(philosopher))
		return (false);
	return (true);
}

static bool	sync_threads_start(t_philosopher *philosopher)
{
	long int	start_time;
	int			exit_code;

	start_time = is_time_started(philosopher);
	while (start_time < 0)
	{
		if (is_simulation_over(philosopher))
			return (false);
		start_time = is_time_started(philosopher);
	}
	philosopher->start_time = start_time;
	if (philosopher->id % 2 != 0)
	{
		if (!print_log(&philosopher->data, philosopher, "is thinking", false))
			return (false);
		exit_code = accurate_sleep(&philosopher->data,
				philosopher->time_to_eat);
		if (exit_code == GETTIMEOFDAY_ERROR || exit_code == SIMULATION_END)
			return (false);
	}
	if (is_simulation_over(philosopher))
		return (false);
	return (true);
}

void	*philosophers_routine(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	if (!sync_threads_start(philosopher))
		return (NULL);
	while (!is_simulation_over(philosopher))
	{
		if (!take_two_forks(philosopher))
			return (NULL);
		if (!eating(philosopher))
		{
			release_forks(philosopher);
			return (NULL);
		}
		if (!release_forks(philosopher))
			return (NULL);
		if (!sleeping(philosopher) || !thinking(philosopher))
			return (NULL);
	}
	return (NULL);
}
