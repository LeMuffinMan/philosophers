/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:12:24 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/14 18:27:00 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int is_a_philo_dead(t_data *data)
{

  return (0);
}

static int did_philo_ate_enough(t_data *data)
{
  int i;
  int count;

  i = 0;
  while (i < data->nb_philo)
  {
    pthread_mutex_unlock(&data->philosophers[i].mutex_nb_meals_eaten);
    if (data->philosophers[i].nb_meals_eaten == data->number_of_times_each_philosopher_must_eat)
      count++;
  }
  if (count == data->nb_philo)
    return (1);
  return (0);
}

void *monitor_routine(void *arg)
{
  t_data *data;

  data = (t_data *)arg;
  while (1)
  {
    if (is_a_philo_dead(data) || did_philo_ate_enough(data)) // besoin du mutex ?
      break ;
    usleep(1000);
  }
  pthread_mutex_lock(&data->mutex_end);
  data->end = 1;
  pthread_mutex_unlock(&data->mutex_end);
  return (0);
  //on check si un philo est mort
  //on check le nombre de repas si on a un nombre de repas a faire
}
