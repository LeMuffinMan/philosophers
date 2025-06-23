/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:18:19 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 18:45:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

void	destroy_forks_mutex(t_data **data, int last_mutex)
{
	while (last_mutex >= 0)
	{
		pthread_mutex_destroy(&((*data)->forks_mutex[last_mutex]));
		last_mutex--;
	}
}

int	destroy_all_data_mutex_and_free(t_data **data)
{
	destroy_forks_mutex(data, (*data)->nb_philo - 1);
	pthread_mutex_destroy(&(*data)->write_mutex);
	pthread_mutex_destroy(&(*data)->time_mutex);
	pthread_mutex_destroy(&(*data)->end_mutex);
	pthread_mutex_destroy(&(*data)->meals_limit_mutex);
	return (print_error_and_free("Threads init failed\n", THREAD_ERROR, data));
}

void	destroy_all_philo_mutex(t_data **data, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&(*data)->philosophers[i].last_meal_mutex);
		pthread_mutex_destroy(&(*data)->philosophers[i].fed_mutex);
		i--;
	}
}

void	free_allocated_memory(t_data **data)
{
	if (!*data)
		return ;
	if ((*data)->forks)
		free((*data)->forks);
	if ((*data)->forks_mutex)
		free((*data)->forks_mutex);
	if ((*data)->threads)
		free((*data)->threads);
	if ((*data)->philosophers)
		free((*data)->philosophers);
	free(*data);
}

int	simulation_end_destroy_and_free(t_data **data, int exit_code)
{
	int	i;

	i = 0;
	while (i < (*data)->nb_philo)
	{
		pthread_join((*data)->threads[i], NULL);
		i++;
	}
	destroy_all_philo_mutex(data, (*data)->nb_philo - 1);
	destroy_forks_mutex(data, (*data)->nb_philo - 1);
	pthread_mutex_destroy(&(*data)->write_mutex);
	pthread_mutex_destroy(&(*data)->time_mutex);
	pthread_mutex_destroy(&(*data)->end_mutex);
	pthread_mutex_destroy(&(*data)->meals_limit_mutex);
	free_allocated_memory(data);
	return (0);
}
