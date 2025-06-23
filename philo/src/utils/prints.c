/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 19:37:52 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	print_error_and_free(char *msg, int exit_code, t_data **data)
{
	printf("%s", msg);
	free_allocated_memory(data);
	return (exit_code);
}

bool	print_log(t_data **data, t_philosopher *philosopher, char *msg)
{
	long int	time;

	pthread_mutex_lock(&philosopher->data->write_mutex);
	pthread_mutex_lock(&philosopher->data->time_mutex);
	if (is_simulation_over(philosopher))
		return (false);
	time = get_time(data);
	if (is_simulation_over(philosopher))
		return (false);
	printf("%ld %d %s\n", time - philosopher->data->start_time, philosopher->id,
		msg);
	pthread_mutex_unlock(&philosopher->data->write_mutex);
	pthread_mutex_unlock(&philosopher->data->time_mutex);
	return (true);
}

int	init_data_print_error_and_free(char *msg, int exit_code, t_data **data)
{
	if (!*data)
		return (0);
	printf("%s", msg);
	free(*data);
	return (exit_code);
}
