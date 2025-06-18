/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:56:22 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/14 18:17:13 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdbool.h>

//renommer init_data
int init_data(t_data **data, char **av)
{
  *data = malloc(sizeof(t_data));
  if (!data || !*data)
    return (-1);
  //avant on veut verifier si on nous envoie un "" "" "" !!!
  //proteger l'overflow
  (*data)->nb_philo = ft_atoi(av[0]);
  if ((*data)->nb_philo < 1) // au moins 1 ?
    return (print_error(av[0], "philosophers", (*data)));
  (*data)->time_to_die = ft_atoi(av[1]);
  if ((*data)->time_to_die < 0) // incorrect ? 
    return (print_error(av[0], "ms to die", (*data)));
  (*data)->time_to_eat = ft_atoi(av[2]);
  if ((*data)->time_to_eat < 0)
    return (print_error(av[0], "ms to eat", (*data)));
  (*data)->time_to_sleep = ft_atoi(av[3]);
  if ((*data)->time_to_sleep < 0)
    return (print_error(av[0], "ms to sleep", (*data)));
  if (av[4]) // on devrait checker la validite des arguments !!!
  {
    (*data)->number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
    if ((*data)->number_of_times_each_philosopher_must_eat < 0)
      return (print_error(av[0], "number of times each philosopher must eat", (*data)));
  }
  else 
    (*data)->number_of_times_each_philosopher_must_eat = -1; // -1 signifie : pas renseigne a l'init !
  (*data)->end = false;
  return (0);
}

int init_mutex(t_data *data)
{
  bool *forks[data->nb_philo];
  pthread_mutex_t fork_mutex[data->nb_philo];
  int i;
  // un mutex pour le print ?

  data->forks = forks;
  i = 0;
  if (pthread_mutex_init(&data->mutex_start, NULL) != 0)
    return (destroy_mutex_free_exit(data, &data->mutex_start, -1, MUTEX_ERROR));
  while (i < data->nb_philo)
  {
    if (pthread_mutex_init(&fork_mutex[i], NULL) != 0)
      return (destroy_mutex_free_exit(data, fork_mutex, i, MUTEX_ERROR));
    i++;
  }
  data->forks = forks;
  return (0);
}

int init_threads(t_data *data)
{
  t_philosopher philosophers[data->nb_philo];
  int i;

  i = 0;
  while (i < data->nb_philo)
  {
    philosophers->id = i + 1;
    philosophers->last_meal = -1; // -1 ?
    philosophers->nb_meals_eaten = 0;
    philosophers->mutex_start = &data->mutex_start;
    i++;
  }
  data->philosophers = philosophers;
  return (0);
}

