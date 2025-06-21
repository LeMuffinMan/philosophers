/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:57:02 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/21 12:24:13 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex_time_mutex(t_data **data)
{
  if (pthread_mutex_init(&(*data)->time_mutex, NULL) != 0)
  {
    destroy_forks_mutex(data, (*data)->nb_philo - 1);
    return (print_error_and_free("Start mutex init failed\n", MUTEX_ERROR, data));
  }
  return (0);
}

int init_mutex_end_mutex(t_data **data)
{
  if (pthread_mutex_init(&(*data)->end_mutex, NULL) != 0)
  {
    destroy_forks_mutex(data, (*data)->nb_philo - 1);
    pthread_mutex_destroy(&(*data)->time_mutex);
    return (print_error_and_free("End mutex init failed\n", MUTEX_ERROR, data));
  }
  return (0);
}

int init_mutex_write_mutex(t_data **data)
{
  if (pthread_mutex_init(&(*data)->write_mutex, NULL) != 0)
  {
    destroy_forks_mutex(data, (*data)->nb_philo - 1);
    pthread_mutex_destroy(&(*data)->time_mutex);
    pthread_mutex_destroy(&(*data)->end_mutex);
    return (print_error_and_free("Write mutex init failed\n", MUTEX_ERROR, data));
  }
  return (0);
}

int init_mutex_meals_limit_mutex(t_data **data)
{
  if (pthread_mutex_init(&(*data)->meals_limit_mutex, NULL) != 0)
  {
    destroy_forks_mutex(data, (*data)->nb_philo -1);
    pthread_mutex_destroy(&(*data)->write_mutex);
    pthread_mutex_destroy(&(*data)->time_mutex);
    pthread_mutex_destroy(&(*data)->end_mutex);
    return (print_error_and_free("meals_limit mutex init failed\n", MUTEX_ERROR, data));
  }
  return (0);
}

int init_philo_struct_mutex(t_data **data, int i)
{
  if (pthread_mutex_init(&(*data)->philosophers[i].last_meal_mutex, NULL) != 0)
  {
    if (i > 0)
    {
      join_threads(data, i);
      destroy_all_philo_mutex(data, i - 1);
    }
    return (destroy_all_data_mutex_and_free(data));
  }
  if (pthread_mutex_init(&(*data)->philosophers[i].nb_meals_eaten_mutex, NULL) != 0)
  {
    pthread_mutex_destroy(&(*data)->philosophers[i].last_meal_mutex);
    if (i > 0)
    {
      join_threads(data, i);
      destroy_all_philo_mutex(data, i - 1);
    }
    return (destroy_all_data_mutex_and_free(data));
  }
  return (0);
}
