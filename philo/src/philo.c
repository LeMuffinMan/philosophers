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
      return (-1);
    i++;
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
  /* exit_code = init_threads(&data); */
  /* if (exit_code != 0) */
  /*   return (exit_code); */
/*   exit_code = monitor_threads(&data); */
  return (exit_code); 
}
