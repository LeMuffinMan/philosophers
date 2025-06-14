/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:26:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/14 18:26:06 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>
#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int start_simulation(t_data *data)
{
  int i;
  struct timeval tv; // je peux declarer cette structure a differents endroits sans foutre le zbeul sur le temps ?

  pthread_mutex_lock(&data->mutex_start);
  i = 0;
  while (i < data->nb_philo)
  {
    if (pthread_create(&data->philosophers[i].thread, NULL, philo_routine, &data->philosophers[i]) != 0)
      return (destroy_mutex_free_exit(data, data->fork_mutex, data->nb_philo, THREAD_ERROR));
  }
  if (pthread_create(&data->monitor, NULL, monitor_routine, &data) != 0)
    return (destroy_mutex_free_exit(data, data->fork_mutex, data->nb_philo, THREAD_ERROR));
  gettimeofday(&tv, NULL);
  data->time_start = tv.tv_sec;
  printf("start time = %d\n", data->time_start);
  pthread_mutex_unlock(&data->mutex_start);
  while (1)
  {
    pthread_mutex_lock(&data->mutex_end);
    if (data->end == 1)
      break ;
    pthread_mutex_unlock(&data->mutex_end);
  }
  return (0);
}

int main (int ac, char **av)
{
  t_data data;
  int exit_code;

  exit_code = 0;
  if (ac < 4 || ac > 5)
  {
    printf("Usage :\n./philo <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> (optionnaly : <number_of_times_each_philosopher_must_eat>)\n");
    //est-ce que le dernier argument doit forcement etre entre corchets ?
    return (1);
  }
  exit_code = init_data(&data, av);
  if (exit_code != 0)
    return (exit_code);
  exit_code = init_mutex(&data);
  if (exit_code != 0)
    return (exit_code);
  exit_code = init_threads(&data);
  if (exit_code != 0)
    return (exit_code);
  exit_code = start_simulation(&data);
  if (exit_code != 0)
    return (exit_code);
  return (exit_code); 
}
