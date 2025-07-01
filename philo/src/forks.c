/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:01 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:42:54 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	only_one_fork_case(t_philosopher *philosopher)
{
	int	exit_code;

	exit_code = accurate_sleep(philosopher->data, philosopher->time_to_die);
	if (exit_code == SIMULATION_END
		|| is_simulation_over(philosopher))
		return (false);
	return (false);
}

bool	take_one_fork(t_philosopher *philosopher, int fork, int fork_in_hand)
{
	if (fork == fork_in_hand)
		return (only_one_fork_case(philosopher));
	pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
	while (philosopher->data->forks[fork] == false)
	{
		if (is_simulation_over(philosopher))
		{
			if (fork_in_hand >= 0)
				set_fork(philosopher, fork_in_hand, true);
			pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
			return (false);
		}
		pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
		usleep(50);
		pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
	}
	philosopher->data->forks[fork] = false;
	pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
	if (!print_log(philosopher->data, philosopher, "has taken a fork", false))
		return (false);
	return (true);
}

bool	take_two_forks(t_philosopher *philosopher)
{
	int	left;
	int	right;

	left = philosopher->id - 1;
	right = philosopher->id % philosopher->nb_philo;
	if (philosopher->id % 2 == 0)
	{
		if (!take_one_fork(philosopher, left, -1))
			return (false);
		if (!take_one_fork(philosopher, right, left))
			return (false);
	}
	else
	{
		if (!take_one_fork(philosopher, right, -1))
			return (false);
		if (!take_one_fork(philosopher, left, right))
			return (false);
	}
	return (true);
}

bool	release_forks(t_philosopher *philosopher)
{
	int		left;
	int		right;

	left = philosopher->id - 1;
	right = (philosopher->id) % philosopher->nb_philo;
	if (is_simulation_over(philosopher))
	{
		set_fork(philosopher, left, true);
		set_fork(philosopher, right, true);
		return (false);
	}
	if (philosopher->id % 2 == 0)
	{
		set_fork(philosopher, left, true);
		set_fork(philosopher, right, true);
	}
	else
	{
		set_fork(philosopher, right, true);
		set_fork(philosopher, left, true);
	}
	if (is_simulation_over(philosopher))
		return (false);
	return (true);
}
