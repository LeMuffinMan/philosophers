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
  print_log(philosopher, THINK);
  accurate_sleep((philosopher->time_to_eat * 2 / philosopher->time_to_sleep));
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
  print_log(philosopher, EAT);
  pthread_mutex_lock(&philosopher->last_meal_mutex);
  pthread_mutex_lock(&philosopher->data->time_mutex);
  philosopher->last_meal = get_time() - philosopher->data->start_time;
  pthread_mutex_unlock(&philosopher->data->time_mutex);
  pthread_mutex_unlock(&philosopher->last_meal_mutex);
  accurate_sleep(philosopher->time_to_eat);
  /* usleep(philosopher->time_to_eat * 1000); */
  philosopher->nb_meals_eaten++;
  /* pthread_mutex_lock(&philosopher->data->write_mutex); */
  /* printf("%d ate %d meals | limit = %d\n", philosopher->id, philosopher->nb_meals_eaten, philosopher->meals_limit); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); */
  if (philosopher->nb_meals_eaten == philosopher->meals_limit)
  {
    /* pthread_mutex_lock(&philosopher->data->write_mutex); */
    /* printf("%d is fed\n", philosopher->id); */
    /* pthread_mutex_unlock(&philosopher->data->write_mutex); */
    pthread_mutex_lock(&philosopher->fed_mutex);
    philosopher->fed = true;
    pthread_mutex_unlock(&philosopher->fed_mutex);
  }
  if (is_simulation_over(philosopher))
    return (1);
  return (0);
}

int sleeping(t_philosopher *philosopher)
{
  if (is_simulation_over(philosopher))
    return (1);
  print_log(philosopher, SLEEP);
  accurate_sleep(philosopher->time_to_sleep);
  if (is_simulation_over(philosopher))
    return (1);
  return (0);
}

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;
  int exit_code;

  exit_code = 0;
  philosopher = (t_philosopher *)arg;
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("id : %d\n", philosopher->id); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  exit_code = is_time_started(philosopher);
  while (!exit_code)
  {
    exit_code = is_time_started(philosopher);
  }
  while (!is_simulation_over(philosopher))
  {
    take_two_forks(philosopher);
    eating(philosopher);
    release_forks(philosopher);
    /* sleeping(philosopher); */
    if (sleeping(philosopher) || thinking(philosopher))
      return (NULL);
  }
  return (NULL);
}

