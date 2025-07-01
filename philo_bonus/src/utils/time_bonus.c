/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:56:13 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 20:24:31 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long int	accurate_sleep(t_simulation *simulation, int time_to_sleep)
{
	long int	start_time;
	long int	time_elapsed;

	start_time = get_time();
	time_elapsed = 0;
	while (time_elapsed < time_to_sleep)
	{
		if (time_elapsed > simulation->data.time.die
			|| am_i_starving(simulation))
		{
			simulation->data.exit_code = 1;
			sem_post(simulation->sems.death);
			return (SIMULATION_END);
		}
		usleep(500);
		time_elapsed = get_time() - start_time;
	}
	return (time_elapsed);
}

bool	am_i_starving(t_simulation *simulation)
{
	if ((get_time()
			- simulation->data.time.last_meal) > simulation->data.time.die)
	{
		simulation->data.exit_code = get_time() - simulation->data.time.start;
		sem_post(simulation->sems.death);
		return (true);
	}
	return (false);
}
