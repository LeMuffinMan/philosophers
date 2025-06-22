/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:13:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/06/20 17:22:29 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> //usleep

int thinking(t_philosopher *philosopher)
{
  if (is_simulation_over(philosopher))
    return (1);
  print_log(philosopher, "is thinking");
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("id : %d started to think at %ld\n", philosopher->id, get_time() - philosopher->data->start_time); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  accurate_sleep((philosopher->time_to_eat * 2 - philosopher->time_to_sleep));
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("id : %d finished to think at %ld\n", philosopher->id, get_time() - philosopher->data->start_time); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  return (0);
  if (is_simulation_over(philosopher))
    return (1);
}

int eating(t_philosopher *philosopher)
{
  if (is_simulation_over(philosopher))
  {
    release_forks(philosopher);
    return (1);
  }
  print_log(philosopher, "is eating");
  philosopher->nb_meals_eaten++;
  if (philosopher->nb_meals_eaten == philosopher->meals_limit)
  {
    pthread_mutex_lock(&philosopher->fed_mutex);
    philosopher->fed = true;
    pthread_mutex_unlock(&philosopher->fed_mutex);
  }
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("id : %d started to eat at %ld\n", philosopher->id, get_time() - philosopher->data->start_time); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  accurate_sleep(philosopher->time_to_eat);
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("id : %d finished to eat at %ld\n", philosopher->id, get_time() - philosopher->data->start_time); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  pthread_mutex_lock(&philosopher->last_meal_mutex);
  philosopher->last_meal = get_time() - philosopher->start_time;
  pthread_mutex_unlock(&philosopher->last_meal_mutex);
  if (is_simulation_over(philosopher))
    return (1);
  return (0);
}

int sleeping(t_philosopher *philosopher)
{
  if (is_simulation_over(philosopher))
    return (1);
  print_log(philosopher, "is sleeping");
  accurate_sleep(philosopher->time_to_sleep);
  if (is_simulation_over(philosopher))
    return (1);
  return (0);
}

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;
  long int start_time;

  philosopher = (t_philosopher *)arg;
  start_time = is_time_started(philosopher);
  while (start_time < 0)
  {
    start_time = is_time_started(philosopher);
  }
  philosopher->start_time = start_time;
  if (philosopher->id % 2 == 0)
    accurate_sleep(10);
  while (!is_simulation_over(philosopher))
  {
    if (!take_two_forks(philosopher))
      return (NULL);
    if (is_simulation_over(philosopher))
      return (NULL);
    eating(philosopher);
    release_forks(philosopher);
    if (sleeping(philosopher) || thinking(philosopher))
      return (NULL);
  }
  return (NULL);
}

