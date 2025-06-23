/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:25:05 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/23 15:25:15 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_struct_last_meal_mutex(t_data **data, int i)
{
	if (pthread_mutex_init(&(*data)->philosophers[i].last_meal_mutex,
			NULL) != 0)
	{
		if (i > 0)
		{
			while (i >= 0)
			{
				pthread_join((*data)->threads[i], NULL);
				i--;
			}
			destroy_all_philo_mutex(data, i - 1);
		}
		return (destroy_all_data_mutex_and_free(data));
	}
	return (0);
}

int	init_philo_struct_fed_mutex(t_data **data, int i)
{
	if (pthread_mutex_init(&(*data)->philosophers[i].fed_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&(*data)->philosophers[i].last_meal_mutex);
		if (i > 0)
		{
			while (i >= 0)
			{
				pthread_join((*data)->threads[i], NULL);
				i--;
			}
			destroy_all_philo_mutex(data, i - 1);
		}
		return (destroy_all_data_mutex_and_free(data));
	}
	return (0);
}

int	init_philo_struct_mutex(t_data **data, int i)
{
	int	exit_code;

	exit_code = init_philo_struct_last_meal_mutex(data, i);
	if (exit_code)
		return (exit_code);
	exit_code = init_philo_struct_fed_mutex(data, i);
	if (exit_code)
		return (exit_code);
	return (0);
}
