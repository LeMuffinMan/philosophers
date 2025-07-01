/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:57:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:41:32 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	is_simulation_over(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->data->end_mutex);
	if (philosopher->data->end)
	{
		pthread_mutex_unlock(&philosopher->data->end_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philosopher->data->end_mutex);
	return (false);
}

long int	is_time_started(t_philosopher *philosopher)
{
	long int	start_time;

	start_time = -1;
	pthread_mutex_lock(&philosopher->data->time_mutex);
	if (philosopher->data->start_time != -1)
		start_time = philosopher->data->start_time;
	pthread_mutex_unlock(&philosopher->data->time_mutex);
	return (start_time);
}

int	accurate_sleep(t_data *data, int time_to_sleep)
{
	int			ret_val;
	long int	start_time;

	start_time = get_time();
	ret_val = get_time();
	while (ret_val < time_to_sleep)
	{
		pthread_mutex_lock(&data->end_mutex);
		if (data->end)
		{
			pthread_mutex_unlock(&data->end_mutex);
			return (SIMULATION_END);
		}
		pthread_mutex_unlock(&data->end_mutex);
		usleep(100);
		ret_val = get_time() - start_time;
	}
	return (ret_val);
}
