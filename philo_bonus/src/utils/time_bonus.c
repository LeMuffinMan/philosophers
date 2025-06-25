/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:57:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:47:14 by oelleaum         ###   ########lyon.fr   */
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

int	accurate_sleep(int time_to_sleep)
{
	int			ret_val;
	long int	start_time;

	start_time = get_time();
	if (start_time == GETTIMEOFDAY_ERROR)
		return (GETTIMEOFDAY_ERROR);
	ret_val = get_time();
	while (ret_val != GETTIMEOFDAY_ERROR && ret_val < time_to_sleep)
	{
		usleep(100);
		ret_val = get_time() - start_time;
	}
	return (ret_val);
}
