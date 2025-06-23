/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 15:40:39 by oelleaum         ###   ########lyon.fr   */
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

int	print_log(t_philosopher *philosopher, char *msg)
{
	pthread_mutex_lock(&philosopher->data->write_mutex);
	pthread_mutex_lock(&philosopher->data->time_mutex);
	if (is_simulation_over(philosopher))
		return (1);
	printf("%ld %d %s\n", get_time() - philosopher->data->start_time,
		philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->data->write_mutex);
	pthread_mutex_unlock(&philosopher->data->time_mutex);
	return (0);
}

int	init_data_print_error_and_free(char *msg, int exit_code, t_data **data)
{
	if (!*data)
		return (0);
	printf("%s", msg);
	free(*data);
	return (exit_code);
}
