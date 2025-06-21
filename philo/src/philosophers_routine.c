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
  print_log(philosopher, THINK);
  usleep(philosopher->time_to_eat * 2 / philosopher->time_to_sleep);
  return (0);
}

int eating(t_philosopher *philosopher)
{
  print_log(philosopher, EAT);
  usleep(philosopher->time_to_eat * 1000);
  pthread_mutex_lock(&philosopher->last_meal_mutex);
  philosopher->last_meal = get_time();
  pthread_mutex_unlock(&philosopher->last_meal_mutex);
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
  return (0);
}

int sleeping(t_philosopher *philosopher)
{
  print_log(philosopher, SLEEP);
  usleep(philosopher->time_to_sleep * 1000);
  return (0);
}

int take_forks(t_philosopher *philosopher)
{
    int left = philosopher->id;
    int right = (philosopher->id + 1) % philosopher->nb_philo;
    
    if (philosopher->id % 2 == 0) {
        pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
        philosopher->data->forks[left] = false;
        print_log(philosopher, TAKE_FORK);
        pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
        philosopher->data->forks[right] = false;
        print_log(philosopher, TAKE_FORK);
    } else {
        pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
        philosopher->data->forks[right] = false;
        print_log(philosopher, TAKE_FORK);
        pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
        philosopher->data->forks[left] = false;
        print_log(philosopher, TAKE_FORK);
    }
    return (0);
}

int release_forks(t_philosopher *philosopher)
{
    int left = philosopher->id;
    int right = (philosopher->id + 1) % philosopher->nb_philo;
    
    pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
    philosopher->data->forks[left] = true;
    /* print_log(philosopher, RELEASE_FORK); */
    pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
    philosopher->data->forks[right] = true;
    /* print_log(philosopher, RELEASE_FORK); */
    return (0);
}

bool is_simulation_over(t_philosopher *philosopher)
{
  pthread_mutex_lock(&philosopher->data->end_mutex);
  if (philosopher->data->end)
  {
    return (true);
    pthread_mutex_unlock(&philosopher->data->end_mutex);
  }
  pthread_mutex_unlock(&philosopher->data->end_mutex);
  return (false);
}

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;

  philosopher = (t_philosopher *)arg;
  pthread_mutex_lock(&philosopher->data->time_mutex); //soit je me sert que de l'etat du mutex, soit je check la valeur de start 
  if (philosopher->data->start_time != -1)
    pthread_mutex_unlock(&philosopher->data->time_mutex); 
  else
    return (NULL); // gestion d'erreur ? on peut ajouter un arg dans le create pour recuperer la valeur de retour 
  while (!is_simulation_over(philosopher))
  {
    thinking(philosopher);
    take_forks(philosopher);
    eating(philosopher);
    release_forks(philosopher);
    sleeping(philosopher);
  }
  return (NULL);
}
