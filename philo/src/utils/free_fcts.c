/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:10:44 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/21 12:29:31 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int init_data_print_error_and_free(char *msg, int exit_code, t_data **data)
{
  if (!*data)
    return (0);
  printf("%s", msg);
  free(*data);
  return (exit_code);
}

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
  int i;

  i = 0;
  while (i < (*data)->nb_philo)
  {
    pthread_join((*data)->threads[i], NULL);
    i++;
  }
  destroy_all_philo_mutex(data, (*data)->nb_philo - 1);
  destroy_forks_mutex(data, (*data)->nb_philo - 1);
  pthread_mutex_destroy(&(*data)->write_mutex);
  pthread_mutex_destroy(&(*data)->time_mutex);
  pthread_mutex_destroy(&(*data)->end_mutex);
  pthread_mutex_destroy(&(*data)->meals_limit_mutex);
  free_allocated_memory(data);
  return (0);
}

