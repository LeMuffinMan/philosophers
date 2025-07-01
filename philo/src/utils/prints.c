/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/07/01 19:40:54 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	print_error_and_free(char *msg, int exit_code, t_data *data)
{
	printf("%s", msg);
	if (data)
		free_allocated_memory(data);
	return (exit_code);
}

bool	print_log(t_data *data, t_philosopher *philosopher, char *msg,
		bool end)
{
	long int	time;

	pthread_mutex_lock(&philosopher->data->time_mutex);
	if (is_simulation_over(philosopher))
	{
		pthread_mutex_unlock(&philosopher->data->time_mutex);
		return (false);
	}
	time = get_time();
	if (is_simulation_over(philosopher))
	{
		pthread_mutex_unlock(&philosopher->data->time_mutex);
		return (false);
	}
	pthread_mutex_lock(&philosopher->data->write_mutex);
	if (end == true)
		set_end(data, &data->end_mutex);
	printf("%ld %d %s\n", time - philosopher->data->start_time, philosopher->id,
		msg);
	pthread_mutex_unlock(&philosopher->data->write_mutex);
	pthread_mutex_unlock(&philosopher->data->time_mutex);
	return (true);
}

int	init_data_print_error(char *msg, int exit_code)
{
	printf("%s", msg);
	return (exit_code);
}
