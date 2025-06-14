/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:26:45 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/01 18:57:44 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>
#include "philo.h"
#include <stdio.h>
#include <pthread.h>

int destroy_mutex_exit(pthread_mutex_t *fork_mutex, int i)
{
  int j;

  j = 0;
  while (j < i)
  {
    pthread_mutex_destroy(fork_mutex[j]);
    j++;
  }
  return (MUTEX_ERROR);
}

int init_mutex(t_data *data)
{
  bool forks[data->nb_philo];
  pthread_mutex_t fork_mutex[data->nb_philo];
  int i;
  // un mutex pour le print ?

  data->forks = forks;
  i = 0;
  while (i < data->nb_philo)
  {
    if (pthread_mutex_init(&fork_mutex[i], NULL) != 0)
      return (destroy_mutex(fork_mutex, i));
    i++;
  }
  data->forks = forks;
  return (0);
}

int init_threads(t_data *data)
{
  pthread_t philosophers[data->nb_philo];
  int i;

  i = 0;
  while (i < data->nb_philo)
  {
    philosophers.id = i + 1;
    philosophers.last_meal = -1; // -1 ?
    philosophers.nb_meals_eaten = 0;
    i++;
  }
  data->philosophers = philosophers;
  return (0);
}

int start_simulation(t_data *data)
{
  int i;

  i = 0;
  while (i < data->nb_philo)
  {
    if (pthread_create(data->philosophers[i]->thread, NULL, routine, data->philosphers[i]) != 0)
      return (-1);
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
  exit_code = init_args(&data, av);
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
