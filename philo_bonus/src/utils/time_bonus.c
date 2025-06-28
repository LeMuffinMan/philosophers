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

long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (GETTIMEOFDAY_ERROR);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	accurate_sleep(t_simulation *simulation, int time_to_sleep)
{
	int			ret_val;
	long int	start_time;

	start_time = get_time();
	if (start_time == GETTIMEOFDAY_ERROR)
		return (GETTIMEOFDAY_ERROR);
	ret_val = get_time();
	while (ret_val != GETTIMEOFDAY_ERROR && ret_val < time_to_sleep)
	{
		if ((get_time() - simulation->data.time.last_meal) > simulation->data.time.die)
			return (SIMULATION_END); // BLOCAGE ICI !!!
		/* if (should_i_stop(simulation) || is_simulation_over(simulation)) */
		/* 	return (SIMULATION_END); */
		usleep(100);
		ret_val = get_time() - start_time;
	}
		/* printf("ret_val = %d\n", ret_val); */
	return (ret_val);
}
