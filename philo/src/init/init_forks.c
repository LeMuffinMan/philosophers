/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:20:03 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/21 12:22:09 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include <stdlib.h>

int init_mutex_forks_bool(t_data **data)
{
  int i;

  (*data)->forks = malloc(sizeof(bool) * (*data)->nb_philo);
  if (!(*data)->forks)
    return (print_error_and_free("forks mem_alloc failed\n", MALLOC_ERROR, data));
  i = 0;
  while (i < (*data)->nb_philo)
  {
    (*data)->forks[i] = false;
    i++;
  }
  return (0);
}

int init_mutex_forks_mutex(t_data **data)
{
  int i;

  (*data)->forks_mutex = malloc(sizeof(pthread_mutex_t) * (*data)->nb_philo);
  if (!(*data)->forks_mutex)
    return (print_error_and_free("forks mem_alloc failed\n", MALLOC_ERROR, data));
  i = 0;
  while (i < (*data)->nb_philo)
  {
    if (pthread_mutex_init(&(*data)->forks_mutex[i], NULL) != 0)
    {
      destroy_forks_mutex(data, i);
      return (print_error_and_free("Forks mutex init failed\n", MUTEX_ERROR, data));
    }
    i++;
  }
  return (0);
}
