
#include <pthread.h>
#include "philo.h"
#include <sys/time.h>
#include <stddef.h> // POUR NULL !!
#include <unistd.h> //usleep

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
    pthread_mutex_unlock(&philosopher->data->end_mutex);
    return (true);
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

int accurate_sleep(int time_to_sleep)
{
  long int start_time;

  start_time = get_time();
  while ((get_time() - start_time) < time_to_sleep)
    usleep(100); 
  return (0);
}
