
#include <pthread.h>
#include "philo.h"
#include <sys/time.h>
#include <stddef.h> // POUR NULL !!
#include <unistd.h> //usleep
#include <stdio.h>

//returns ms elapsed since 1 january 1970
long int get_time(void)
{
  struct timeval tv;
  
  gettimeofday(&tv, NULL);
  //gerer l'erreur du gettimeofday ? 
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)); 
}
bool is_simulation_over(t_philosopher *philosopher)
{
  pthread_mutex_lock(&philosopher->data->end_mutex);
  if (philosopher->data->end)
  {
    /* pthread_mutex_lock(&philosopher->data->write_mutex); */
    /* printf("id leaving %d\n", philosopher->id); */
    /* pthread_mutex_unlock(&philosopher->data->write_mutex); */
    pthread_mutex_unlock(&philosopher->data->end_mutex);
    return (true);
  }
  pthread_mutex_unlock(&philosopher->data->end_mutex);
  return (false);
}

long int is_time_started(t_philosopher *philosopher)
{
  long int start_time;

  start_time = false;
  pthread_mutex_lock(&philosopher->data->time_mutex); 
  if (philosopher->data->start_time != -1)
    start_time = philosopher->data->start_time;
  pthread_mutex_unlock(&philosopher->data->time_mutex); 
  return (start_time);
}

int accurate_sleep(int time_to_sleep)
{
  long int start_time;

  start_time = get_time();
  while ((get_time() - start_time) < time_to_sleep)
    usleep(100); 
  return (0);
}
