/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:10:01 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 19:33:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static bool	try_to_catch_fork(t_philosopher *philosopher, int fork_to_catch)
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

bool	take_two_forks(t_philosopher *philosopher)
{
	int	left;
	int	right;

	left = philosopher->id - 1;
	right = (philosopher->id) % philosopher->nb_philo;
	if (left < right)
	{
		left = (philosopher->id) % philosopher->nb_philo;
		right = philosopher->id - 1;
	}
	/* if (philosopher->id == 1) */
	/* 	printf("trying to catch fork %d and %d\n", left, right); */
	if (!try_to_catch_fork(philosopher, left))
		return (false);
	if (!try_to_catch_fork(philosopher, right))
	{
		set_fork(philosopher, left, true);
		return (false);
	}
	return (true);
}

bool	release_forks(t_philosopher *philosopher)
{
	int		left;
	int		right;
	bool	exit_code;

	left = philosopher->id - 1;
	right = (philosopher->id) % philosopher->nb_philo;
	if (is_simulation_over(philosopher))
		return (false);
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
		return (false);
	/* if (philosopher->id != 1) */
	/* 	printf("caught fork %d and %d\n", left, right); */
	return (true);
}
