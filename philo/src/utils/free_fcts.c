/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:10:44 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/19 18:46:55 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int free_allocated_memory(t_data **data)
{
  if (!*data)
    return (0);
  if ((*data)->forks)
    free((*data)->forks);
  if ((*data)->forks_mutex)
    free((*data)->forks_mutex);
  if ((*data)->threads)
    free((*data)->threads);
  if ((*data)->philosophers)
    free((*data)->philosophers);
  free(*data);
  return (0);
}

int simulation_end_destroy_and_free(t_data **data)
{
  join_threads(data, (*data)->nb_philo - 1);
  pthread_join((*data)->monitor, NULL);
  destroy_all_philo_mutex(data, (*data)->nb_philo - 1);
  destroy_forks_mutex(data, (*data)->nb_philo - 1);
  pthread_mutex_destroy(&(*data)->write_mutex);
  pthread_mutex_destroy(&(*data)->start_mutex);
  pthread_mutex_destroy(&(*data)->end_mutex);
  pthread_mutex_destroy(&(*data)->meals_limit_mutex);
  free_allocated_memory(data);
  return (0);
}

/* int destroy_mutex_free_exit(t_data *data, pthread_mutex_t *fork_mutex, int i, int exit_code) */
/* { */
/*   int j; */
/**/
/*   pthread_mutex_destroy(&data->mutex_start); */
/*   j = 0; */
/*   while (i > 0 && j < i) */
/*   { */
/*     pthread_mutex_destroy(&fork_mutex[j]); */
/*     j++; */
/*   } */
/*   //free(data->philo); */
/*   free(data); */
/*   //on join les threads crees seulement */
/*   return (exit_code); */
/* } */
