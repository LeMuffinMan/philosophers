/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:18:19 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/21 12:22:31 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int destroy_forks_mutex(t_data **data, int last_mutex)
{
  while (last_mutex >= 0)
  {
    pthread_mutex_destroy(&((*data)->forks_mutex[last_mutex]));
    last_mutex--;
  }
  return (0);
}

int destroy_all_data_mutex_and_free(t_data **data)
{
    destroy_forks_mutex(data, (*data)->nb_philo - 1);
    pthread_mutex_destroy(&(*data)->write_mutex);
    pthread_mutex_destroy(&(*data)->start_mutex);
    pthread_mutex_destroy(&(*data)->end_mutex);
    pthread_mutex_destroy(&(*data)->meals_limit_mutex);
    return (print_error_and_free("Threads init failed\n", THREAD_ERROR, data));
}

int destroy_all_philo_mutex(t_data **data, int i)
{
  while (i >= 0)
  {
    pthread_mutex_destroy(&(*data)->philosophers[i].last_meal_mutex);
    pthread_mutex_destroy(&(*data)->philosophers[i].nb_meals_eaten_mutex);
    i--;
  }
  return (0);
}
