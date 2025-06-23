/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:01 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 17:12:27 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

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

bool	try_to_catch_fork(t_philosopher *philosopher, int fork_to_catch)
{
	while (!get_fork_state(philosopher, fork_to_catch))
	{
		if (is_simulation_over(philosopher))
			return (false);
		usleep(100);
		if (is_simulation_over(philosopher))
			return (false);
	}
	return (true);
}

int	set_fork(t_philosopher *philosopher, int fork, bool state)
{
	pthread_mutex_lock(&philosopher->data->forks_mutex[fork]);
	philosopher->data->forks[fork] = state;
	pthread_mutex_unlock(&philosopher->data->forks_mutex[fork]);
	return (0);
}

bool	take_two_forks(t_philosopher *philosopher)
{
	int	left;
	int	right;

	left = philosopher->id;
	right = (philosopher->id + 1) % philosopher->nb_philo;
	if (left < right)
	{
		left = (philosopher->id + 1) % philosopher->nb_philo;
		right = philosopher->id;
	}
	if (!try_to_catch_fork(philosopher, left))
		return (false);
	if (!try_to_catch_fork(philosopher, right))
	{
		set_fork(philosopher, left, true);
		return (false);
	}
	return (true);
}

int	release_forks(t_philosopher *philosopher)
{
	int		left;
	int		right;
	bool	exit_code;

	left = philosopher->id;
	right = (philosopher->id + 1) % philosopher->nb_philo;
	if (is_simulation_over(philosopher))
		return (1);
	if (left > right)
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
		return (1);
	return (0);
}
