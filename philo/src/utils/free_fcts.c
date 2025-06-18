/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:10:44 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/14 18:17:39 by oelleaum         ###   ########lyon.fr   */
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
  free(*data);
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
