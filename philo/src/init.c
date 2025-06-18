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

//revoir les valeurs mins 
int init_data(t_data **data, char **av)
{
  *data = malloc(sizeof(t_data));
  if (!*data)
    return (print_error_and_free("Data struct mem_alloc failed\n", MALLOC_ERROR, *data));
  //on peut lancer 0 philo ?
  (*data)->nb_philo = ft_atoi(av[1]); // overflow ?
  if ((*data)->nb_philo <= 0)
    return (print_error_and_free("Incorrect number_of_philosophers\n", INVALID_ARG, *data));
  //un time to die de 0 ? 
  (*data)->time_to_die = ft_atoi(av[2]); // overflow ?
  if ((*data)->time_to_die <= 0)
    return (print_error_and_free("Incorrect time_to_die\n", INVALID_ARG, *data));
  //un time to eat de 0 ? 
  (*data)->time_to_eat = ft_atoi(av[3]); // overflow ?
  if ((*data)->time_to_eat <= 0)
    return (print_error_and_free("Incorrect time_to_eat\n", INVALID_ARG, *data));
  //un time to sleep de 0 ? 
  (*data)->time_to_sleep = ft_atoi(av[4]); // overflow ?
  if ((*data)->time_to_sleep <= 0)
    return (print_error_and_free("Incorrect time_to_sleep\n", INVALID_ARG, *data));
  if (av[5])
  {
    //un min de 0 ? 
    (*data)->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    if ((*data)->number_of_times_each_philosopher_must_eat <= 0)
      return (print_error_and_free("Incorrect number_of_times_each_philosopher_must_eat", INVALID_ARG, *data));
  }
  else 
    (*data)->number_of_times_each_philosopher_must_eat = -1; // set a -1 si pas renseigne par user 
  return (0);
}

/* int free_destroy_exit(t_data *data, int exit_code, int last_mutex) */
/* { */
/*   int i; */
/*    */
/*   if (data->forks) */
/*   { */
/*     i = 0; */
/*     while (i < (*data)->nb_philo) */
/*     { */
/*       free(data->forks[i]); */
/*       i++; */
/*     } */
/*     free(data->forks); */
/*   } */
/*   i = 0; */
/*   while (last_mutex > 0 && i < last_mutex) */
/*   { */
/*     pthread_mutex_destroy(&data->fork_mutex[i]); */
/*     i++; */
/*   } */
/*   if (data->fork_mutex) */
/*   { */
/*     i = 0; */
/*     while (i < (*data)->nb_philo) */
/*     { */
/*       free(data->fork_mutex[i]); */
/*       i++; */
/*     } */
/*     free(data->fork_mutex); */
/*   } */
/*   free(*data); */
/*   return (exit_code); */
/* } */
/**/
/* int init_forks(t_data *data) */
/* { */
/*   bool *forks; */
/*   pthread_mutex_t *fork_mutex; */
/*   int i; */
/*   // un mutex pour le print ? */
/**/
/*   data->forks = malloc(sizeof(bool) * (*data)->nb_philo); */
/*   if (!data->forks || !(*data)->forks) */
/*     return (free_destroy_exit(data, MALLOC_ERROR, 0)); */
/*   data->fork_mutex = malloc(sizeof(pthread_mutex_t) & (*data)->nb_philo); */
/*   if (!data->fork_mutex || !(*data)->fork_mutex) */
/*     return (free_destroy_exit(data, MALLOC_ERROR, 0)); */
/*   i = 0; */
/*   while (i < data->nb_philo) */
/*   { */
/*     if (pthread_mutex_init(&fork_mutex[i], NULL) != 0) */
/*       return (free_destroy_exit(data, MUTEX_ERROR, i)); */
/*     i++; */
/*   } */
  /* if (pthread_mutex_init(&data->mutex_start, NULL) != 0) */
  /*   return (destroy_mutex_free_exit(data, &data->mutex_start, -1, MUTEX_ERROR)); */
/*   return (0); */
/* } */
/**/
/* int init_threads(t_data *data) */
/* { */
/*   t_philosopher philosophers[data->nb_philo]; */
/*   int i; */
/**/
/*   i = 0; */
/*   while (i < data->nb_philo) */
/*   { */
/*     philosophers->id = i + 1; */
/*     philosophers->last_meal = -1; // -1 ? */
/*     philosophers->nb_meals_eaten = 0; */
/*     philosophers->mutex_start = &data->mutex_start; */
/*     i++; */
/*   } */
/*   data->philosophers = philosophers; */
/*   return (0); */
/* } */

