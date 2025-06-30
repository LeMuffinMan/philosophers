/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:56:13 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/27 18:56:15 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (GETTIMEOFDAY_ERROR);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long int	accurate_sleep(t_simulation *simulation, int time_to_sleep)
{
	int			ret_val;
	long int	start_time;
	long int time_elapsed;

	start_time = get_time();
	if (start_time == GETTIMEOFDAY_ERROR)
		return (GETTIMEOFDAY_ERROR);
	time_elapsed = 0;
	while (time_elapsed < time_to_sleep)
	{
		if (time_elapsed > simulation->data.time.die)
		{
  		sem_wait(simulation->sems.print);
  		/* printf("%ld %d died\n", time_elapsed, simulation->data.id); */
  		sem_post(simulation->sems.death);
  		sem_post(simulation->sems.print);
  		return (SIMULATION_END);
		}
		usleep(500);

		time_elapsed = get_time() - start_time;
	}
	return (time_elapsed);
}
