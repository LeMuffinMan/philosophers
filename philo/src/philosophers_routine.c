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


bool are_philo_fed(t_data **data)
{
  int i;

  i = 0;
  while (i < (*data)->nb_philo)
  {
    pthread_mutex_lock(&(*data)->philosophers[i].fed_mutex);
    if ((*data)->philosophers[i].fed == false)
    {
      pthread_mutex_unlock(&(*data)->philosophers[i].fed_mutex);
      return (false);
    }
    pthread_mutex_unlock(&(*data)->philosophers[i].fed_mutex);
    i++;
  }
  return (true);
}

int accurate_sleep(int time_to_sleep)
{
  int elapsed_time;

  elapsed_time = 0;
  while (elapsed_time < time_to_sleep)
  {
    usleep(time_to_sleep);
    time_to_sleep = time_to_sleep / 2;
  }
  return (0);
}

int thinking(t_philosopher *philosopher)
{
  print_log(philosopher, THINK);
  usleep(philosopher->time_to_eat * 2 / philosopher->time_to_sleep);
  return (0);
}

int eating(t_philosopher *philosopher)
{
  print_log(philosopher, EAT);
  accurate_sleep(philosopher->time_to_eat * 1000);
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
  accurate_sleep(philosopher->time_to_sleep * 1000);
  return (0);
}

bool take_one_fork(t_philosopher *philosopher, int i)
{
  bool exit_code;
  exit_code = false;
  pthread_mutex_lock(&philosopher->data->forks_mutex[i]);
  if (philosopher->data->forks[i] == false)
  {
    printf("fork %d taken\n", i);
    exit_code = true;
    philosopher->data->forks[i] = true;
  }
  pthread_mutex_unlock(&philosopher->data->forks_mutex[i]);
  return (exit_code);
}

bool take_two_forks(t_philosopher *philosopher)
{
  int left;
  int right;
  bool exit_code;

  left = philosopher->id;
  right = philosopher->id + 1 % 2;
  if (left > right)
  {
    exit_code = take_one_fork(philosopher, left);
    while (!exit_code)
      exit_code = take_one_fork(philosopher, left);
    exit_code = take_one_fork(philosopher, right);
    while (!exit_code)
      exit_code = take_one_fork(philosopher, right);
    return (exit_code);
  }
  else
  {
    exit_code = take_one_fork(philosopher, right);
    while (!exit_code)
      exit_code = take_one_fork(philosopher, right);
    exit_code = take_one_fork(philosopher, left);
    while (!exit_code)
      exit_code = take_one_fork(philosopher, left);
    return (exit_code);
  }
}

int release_forks(t_philosopher *philosopher)
{
  int left;
  int right;
  bool exit_code;

  left = philosopher->id;
  right = philosopher->id + 1 % 2;
  pthread_mutex_lock(&philosopher->data->forks_mutex[left]);
  philosopher->data->forks[left] = false;
  pthread_mutex_unlock(&philosopher->data->forks_mutex[left]);
  pthread_mutex_lock(&philosopher->data->forks_mutex[right]);
  philosopher->data->forks[right] = false;
  pthread_mutex_unlock(&philosopher->data->forks_mutex[right]);
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

bool is_time_started(t_philosopher *philosopher)
{
  bool exit_code;

  exit_code = false;
  pthread_mutex_lock(&philosopher->data->time_mutex); 
  if (philosopher->data->start_time != -1)
    exit_code = true;
  pthread_mutex_unlock(&philosopher->data->time_mutex); 
  return (exit_code);
}

void *philosophers_routine(void *arg)
{    
  t_philosopher *philosopher;
  int exit_code;

  exit_code = 0;
  philosopher = (t_philosopher *)arg;
  exit_code = is_time_started(philosopher);
  //REOVIR ICI !!!
  pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex
  printf("exit_code = %d | id : %d\n", exit_code, philosopher->id);
  pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex
  while (!exit_code)
  {

    exit_code = is_time_started(philosopher);
  }
  while (!is_simulation_over(philosopher))
  {
    take_two_forks(philosopher);
    eating(philosopher);
    release_forks(philosopher);
    sleeping(philosopher);
    thinking(philosopher);
  }
  /* pthread_mutex_lock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  /* printf("ici : %d\n", philosopher->id); */
  /* pthread_mutex_unlock(&philosopher->data->write_mutex); // le write mutex doit etre prio sur le time mutex */
  return (NULL);
}

int main_thread_monitoring(t_data **data) // a bouger !
{
  pthread_mutex_lock(&(*data)->write_mutex);
  printf("monitor started at %ld\n", get_time() - (*data)->start_time);
  pthread_mutex_unlock(&(*data)->write_mutex);
  while (1)
  {
    if (are_philo_fed(data))
    {
      pthread_mutex_lock(&(*data)->end_mutex);
      (*data)->end = true;
      pthread_mutex_unlock(&(*data)->end_mutex);
      return (1);
      /* pthread_mutex_lock(&(*data)->write_mutex); */
      /* printf("DONE !\n"); */
      /* pthread_mutex_unlock(&(*data)->write_mutex); */
    }
    accurate_sleep (1000);
  }
  return (0);
}
