/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:22 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 15:20:42 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* #include <stdbool.h> */
#include <stdlib.h>

int	init_data(t_data **data, char **av)
{
	int	exit_code;

	*data = malloc(sizeof(t_data));
	if (!*data)
		return (init_data_print_error_and_free("Data struct mem_alloc failed\n",
				MALLOC_ERROR, data));
	exit_code = init_user_inputs(data, av);
	if (exit_code)
		return (exit_code);
	(*data)->end = false;
	(*data)->start_time = -1;
	return (0);
}

int	init_mutex(t_data **data)
{
	int	i;
	int	exit_code;

	exit_code = init_mutex_forks_bool(data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex_forks_mutex(data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex_time_mutex(data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex_end_mutex(data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex_write_mutex(data);
	if (exit_code != 0)
		return (exit_code);
	exit_code = init_mutex_meals_limit_mutex(data);
	if (exit_code != 0)
		return (exit_code);
	return (0);
}

int	init_philo_struct(t_data **data, int i)
{
	(*data)->philosophers[i].nb_philo = (*data)->nb_philo;
	(*data)->philosophers[i].time_to_die = (*data)->time_to_die;
	(*data)->philosophers[i].time_to_eat = (*data)->time_to_eat;
	(*data)->philosophers[i].time_to_sleep = (*data)->time_to_sleep;
	(*data)->philosophers[i].id = i;
	(*data)->philosophers[i].last_meal = 0;
	(*data)->philosophers[i].nb_meals_eaten = 0;
	(*data)->philosophers[i].data = *data;
	(*data)->philosophers[i].fed = false;
	(*data)->philosophers[i].meals_limit = (*data)->meals_limit;
	return (init_philo_struct_mutex(data, i));
}

int	create_philosopher(t_data **data, int id)
{
	if (pthread_create(&(*data)->threads[id], NULL, philosophers_routine,
			&(*data)->philosophers[id]) != 0)
	{
		if (id > 0)
		{
			while (id >= 0)
			{
				pthread_join((*data)->threads[id], NULL);
				id--;
			}
		}
		destroy_all_philo_mutex(data, id);
		return (destroy_all_data_mutex_and_free(data));
	}
	return (0);
}

int	init_threads(t_data **data)
{
	int	i;

	(*data)->threads = malloc(sizeof(pthread_t) * (*data)->nb_philo);
	if (!(*data)->threads)
		return (destroy_all_data_mutex_and_free(data));
	(*data)->philosophers = malloc(sizeof(t_philosopher) * (*data)->nb_philo);
	if (!(*data)->philosophers)
		return (destroy_all_data_mutex_and_free(data));
	pthread_mutex_lock(&(*data)->time_mutex);
	i = 0;
	while (i < (*data)->nb_philo)
	{
		init_philo_struct(data, i);
		create_philosopher(data, i);
		i++;
	}
	(*data)->start_time = get_time();
	pthread_mutex_unlock(&(*data)->time_mutex);
	return (0);
}
