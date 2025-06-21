/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:22 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/21 12:25:21 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//revoir les valeurs mins 
int init_data(t_data **data, char **av)
{
  *data = malloc(sizeof(t_data));
  if (!*data)
    return (init_data_print_error_and_free("Data struct mem_alloc failed\n", MALLOC_ERROR, data));
  (*data)->nb_philo = ft_atoi(av[1]); // overflow ?
  if ((*data)->nb_philo <= 0)
    return (init_data_print_error_and_free("Incorrect number_of_philosophers\n", INVALID_ARG, data));
  (*data)->time_to_die = ft_atoi(av[2]); // overflow ?
  if ((*data)->time_to_die <= 0)
    return (init_data_print_error_and_free("Incorrect time_to_die\n", INVALID_ARG, data));
  (*data)->time_to_eat = ft_atoi(av[3]); // overflow ?
  if ((*data)->time_to_eat <= 0)
    return (init_data_print_error_and_free("Incorrect time_to_eat\n", INVALID_ARG, data));
  (*data)->time_to_sleep = ft_atoi(av[4]); // overflow ?
  if ((*data)->time_to_sleep <= 0)
    return (init_data_print_error_and_free("Incorrect time_to_sleep\n", INVALID_ARG, data));
  if (av[5])
  {
    (*data)->meals_limit = ft_atoi(av[5]);
    if ((*data)->meals_limit <= 0)
      return (init_data_print_error_and_free("Incorrect number_of_times_each_philosopher_must_eat\n", INVALID_ARG, data));
  }
  else 
    (*data)->meals_limit = -1; // set a -1 si pas renseigne par user 
  (*data)->end = false;
  (*data)->start_time = -1;
  return (0);
}

int init_mutex(t_data **data)
{
  int i;
  int exit_code;

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

int init_philo_struct(t_data **data, int i)
{
  (*data)->philosophers[i].nb_philo = (*data)->nb_philo;
  (*data)->philosophers[i].time_to_die = (*data)->time_to_die;
  (*data)->philosophers[i].time_to_eat = (*data)->time_to_eat;
  (*data)->philosophers[i].time_to_sleep = (*data)->time_to_sleep;
  (*data)->philosophers[i].id = i; // attention au 0 !
  (*data)->philosophers[i].last_meal = -1;
  (*data)->philosophers[i].nb_meals_eaten = 0;
  (*data)->philosophers[i].data = *data;
  /* (*data)->philosophers[i].start_time = &((*data)->start_time); */
  /* (*data)->philosophers[i].time_mutex = &((*data)->time_mutex); */
  /* (*data)->philosophers[i].end_mutex = &((*data)->end_mutex); */
  /* (*data)->philosophers[i].threads = (*data)->threads; */
  /* (*data)->philosophers[i].write_mutex = &(*data)->write_mutex; */
  return (init_philo_struct_mutex(data, i));
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

int init_threads(t_data **data)
{
  int i;

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
  pthread_mutex_unlock(&(*data)->time_mutex);
  return (0);
}
