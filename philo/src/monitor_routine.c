
#include <pthread.h>
#include "philo.h"
#include <unistd.h> //usleep
#include <stdio.h> // a virerr !!!!

bool get_fed_state(t_philosopher *philosopher)
{
  bool state;

  pthread_mutex_lock(&philosopher->fed_mutex);
  state = philosopher->fed;
  pthread_mutex_unlock(&philosopher->fed_mutex);
  return (state);
}

long int get_last_meal_time(t_philosopher *philosopher)
{
  long int last_meal_time;
  pthread_mutex_lock(&philosopher->last_meal_mutex);
  last_meal_time = philosopher->last_meal;
  pthread_mutex_unlock(&philosopher->last_meal_mutex);
  return (last_meal_time);
}

int set_end(t_data **data, pthread_mutex_t *mutex)
{
  pthread_mutex_lock(mutex);
  (*data)->end = true;
  pthread_mutex_unlock(mutex);
  return (0);
}

bool are_philo_fed(t_data **data)
{
  int i;

  i = 0;
  while (i < (*data)->nb_philo)
  {
    if (!get_fed_state(&(*data)->philosophers[i]))
      return (false);
    i++;
  }
  set_end(data, &(*data)->end_mutex);
  return (true);
}

int are_philo_starving(t_data **data)
{
  int i;
  long int time_elapsed;
  long int last_meal_time;

  i = 0;
  while (i < (*data)->nb_philo)
  {
    last_meal_time = get_last_meal_time(&(*data)->philosophers[i]);
    pthread_mutex_lock(&(*data)->time_mutex);
    time_elapsed = get_time() - (*data)->start_time - last_meal_time;
    pthread_mutex_unlock(&(*data)->time_mutex);
    /* pthread_mutex_lock(&(*data)->write_mutex); */
    /* printf("time elapsed : %ld\n", time_elapsed); */
    /* pthread_mutex_unlock(&(*data)->write_mutex); */
    if (last_meal_time >= 0 && time_elapsed > (*data)->time_to_die)
    {
      pthread_mutex_lock(&(*data)->write_mutex);
      printf("last_meal_time = %ld | time elapsed = %ld\n", last_meal_time, time_elapsed);
      pthread_mutex_unlock(&(*data)->write_mutex);
      print_log(&(*data)->philosophers[i], DIE);
      set_end(data, &(*data)->end_mutex);
      return (true);
    }
    i++;
  }
  return (false);
}

int main_thread_monitoring(t_data **data) // a bouger !
{
  int exit_code;

  exit_code = false;
  /* pthread_mutex_lock(&(*data)->write_mutex); */
  /* printf("monitor started at %ld\n", get_time() - (*data)->start_time); */
  /* pthread_mutex_unlock(&(*data)->write_mutex); */
  while (1)
  {
    //avec un temps de mort tres court, les threads partent quand meme !
    exit_code = are_philo_fed(data);
    //LE PB EST ICI !!
    if (exit_code)
    {
      pthread_mutex_lock(&(*data)->write_mutex);
      printf("fed exit_code = %d\n", exit_code);
      pthread_mutex_unlock(&(*data)->write_mutex);
      return (exit_code);
    }
    exit_code = are_philo_starving(data);
    if (exit_code)
    {
      pthread_mutex_lock(&(*data)->write_mutex);
      printf("starve exit_code = %d\n", exit_code);
      pthread_mutex_unlock(&(*data)->write_mutex);
      return (exit_code);
    }
    accurate_sleep (5);
    /* usleep(100); */
  }
  return (0);
}
