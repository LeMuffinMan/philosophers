/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:01:21 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/20 17:40:37 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include <stdio.h>

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

int join_threads(t_data **data, int i)
{
  while (i >= 0)
  {
    pthread_join((*data)->threads[i], NULL);
    i--;
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

int init_philo_struct(t_data **data, int i)
{
  (*data)->philosophers[i].id = i; // attention au 0 !
  (*data)->philosophers[i].last_meal = -1;
  (*data)->philosophers[i].nb_meals_eaten = 0;
  (*data)->philosophers[i].start_time = &((*data)->start_time);
  (*data)->philosophers[i].start_mutex = &((*data)->start_mutex);
  (*data)->philosophers[i].end_mutex = &((*data)->end_mutex);
  (*data)->philosophers[i].threads = (*data)->threads;
  (*data)->philosophers[i].write_mutex = &(*data)->write_mutex;
  return (init_philo_struct_mutex(data, i));
}

int init_threads(t_data **data)
{
  int i;

  (*data)->threads = malloc(sizeof(pthread_t) * (*data)->nb_philo);
  if (!(*data)->threads)
    return (destroy_all_data_mutex_and_free(data));
  (*data)->philosophers = malloc(sizeof(t_philosopher) * (*data)->nb_philo);
  if (!(*data)->philosophers)
    return (destroy_all_data_mutex_and_free(data));
  pthread_mutex_lock(&(*data)->start_mutex);
  i = 0;
  while (i < (*data)->nb_philo)
  {
    init_philo_struct(data, i);
    if (pthread_create(&(*data)->threads[i], NULL, philosophers_routine, &(*data)->philosophers[i]) != 0)
    {
      if (i > 0)
        join_threads(data, i);
      destroy_all_philo_mutex(data, i);
      return (destroy_all_data_mutex_and_free(data));
    }
    i++;
  }
  (*data)->start_time = get_time();
  printf("init time = %ld\n", (*data)->start_time);
  pthread_mutex_unlock(&(*data)->start_mutex);
  return (0);
}
